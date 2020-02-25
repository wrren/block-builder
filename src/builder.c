/************************************************************************
 *									*
 * Upfront Analytics		   					*
 * Speed Stampede Block Creator						*
 *									*
 * Author: 	Warren Kenny	<warren@ufa.ie>				*
 * 									*
 * Copyright 2014 Upfront Analytics. All rights reserved.		*
 *									*
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <options/builder_options.h>
#include <image/compositor.h>
#include <io/sheet_reader.h>
#include <io/sheet_writer.h>
#include <io/image_writer.h>
#include <wand/magick_wand.h>

#define MAX_INPUT_SHEETS 32

typedef struct
{
	char* 		block;
	sprite_sheet	sheet;
} block_sheet;

/**
 *	Main entry point to block-builder. Expects a set of command-line
 *	arguments indicating the location of the input images, the image IDs
 *	to combine and the output path
 */
int main( int argc, char** argv )
{
	options opt = options_init();
	options_parse( argc, argv, opt );

	MagickWand* 		wand = NewMagickWand();
		
	size_t 			m_width 	= 0,
				m_height 	= 0,
				o_width, 
				o_height,
				sheet_index	= 0,
				sheet_count	= 0;

	block_sheet inputs[MAX_INPUT_SHEETS];
	
	options_get_dimensions( opt, &o_width, &o_height );
	
	sprite_sheet sheet = sheet_init();
	
	char* 			block 		= NULL;
	char* 			input_path	= options_input_path( opt );
	char 			image_path[1024];
	char			sheet_path[1024];

	while( ( block = options_next_block( opt ) ) != NULL )
	{
		inputs[sheet_count].block = block;
		inputs[sheet_count].sheet = sheet_init();

		sprintf( image_path, "%s/%s.jpg", input_path, block );
		sprintf( sheet_path, "%s/%s.bin", input_path, block );
		
		sprite s;

		FILE* sheet_bin = fopen( sheet_path, "r" );

		if( sheet_bin == NULL )
		{
			fprintf( stderr, "Unable to Open Input Block Sheet Binary ( %s ) at Path %s\n", block, sheet_path );
			return -1;
		}

		if( read_bin( inputs[sheet_count].sheet, sheet_bin ) )
		{
			fprintf( stderr, "Error While Reading Block Sheet Binary ( %s ) at Path %s\n", block, sheet_path );
			return -1;
		}

		if( MagickReadImage( wand, image_path ) )
		{
			sprite_init( &s, block, image_path, 0, 0, 0, 0 );
			sheet_add_sprite( sheet, &s );
		}
		else
		{
			fprintf( stderr, "Failed to Read Image at Path %s\n", image_path );
			return -1;
		}

		++sheet_count;
	}

	if( sheet_count == 0 )
	{
		return 0;
	}

	MagickResetIterator( wand );

	while( MagickNextImage( wand ) )
	{
		sprite* s = sheet_next_sprite( sheet );

		s->width 	= MagickGetImageWidth( wand );
		s->height	= MagickGetImageHeight( wand );

		m_width 	= s->width > m_width ? s->width : m_width;
		m_height	= s->height > m_height ? s->height : m_height;
	}

	// wand = DestroyMagickWand( wand );
	sheet_reset_iterator( sheet );	
	arrange( sheet, m_width, m_height, o_width, o_height );
	sheet_reset_iterator( sheet );

	sprite* s;

	// Iterate over the rearranged sheet
	while( ( s = sheet_next_sprite( sheet ) ) != NULL )
	{
		// Find the input sheet with the matching block name
		for( int i = 0; i < sheet_count; i++ )
		{
			if( strcmp( inputs[i].block, s->name ) == 0 )
			{
				// Apply the new offsets to the sheet's internal sprites
				sheet_apply_offset( inputs[i].sheet, s->x, s->y );
				break;
			}
		}
	}

	sheet_dump( inputs[0].sheet );

	// Concatenate all sheets together
	for( int i = 1; i < sheet_count; i++ )
	{
		sheet_concat( inputs[0].sheet, inputs[i].sheet );
	}

	sheet_dump( inputs[0].sheet );

	FILE* sheet_file	= fopen( options_sheet_path( opt ), "w" );
	FILE* image_file	= fopen( options_image_path( opt ), "w" );

	jpg_write( sheet, image_file, o_width, o_height, options_compression_quality( opt ) );
	write_xml( inputs[0].sheet, sheet_file );

	options_free( opt );

	fclose( image_file );
	fclose( sheet_file );

	return 0;
}