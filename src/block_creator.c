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
#include <options/creator_options.h>
#include <io/sheet_writer.h>
#include <io/image_writer.h>
#include <image/compositor.h>
#include <wand/magick_wand.h>

void image_id( char* filename, char* out )
{
	char* dot = strchr( filename, '.' );
	int length = strlen( filename );

	if( dot != NULL )
	{
		length = dot - filename;
	}

	strncpy( out, filename, length );
	out[length] = '\0';
}

void print_usage( FILE* stream )
{
	fprintf( stream, "Usage:\n" );
	fprintf( stream, "\tblock-creator 	--input-dir <image input directory>\n" );
	fprintf( stream, "\t\t\t--sheet <sheet descriptor output path>\n" );
	fprintf( stream, "\t\t\t--image <sheet image output path>\n" );
	fprintf( stream, "\t\t\t--max-width <sprite max width>\n" );
	fprintf( stream, "\t\t\t--max-height <sprite max height>\n" );
	fprintf( stream, "\t\t\t--out-width <sheet image output width>\n" );
	fprintf( stream, "\t\t\t--out-height <sheet image output height>\n" );
	fprintf( stream, "\t\t\t--quality <sheet image output quality>\n" );
	fprintf( stream, "\t\t\tinput file names...\n" );
}

/**
 *	Main entry point to block-creator. Expects a set of command-line
 *	arguments indicating the location of the input images, the image file names
 *	to combine and the output path
 */
int main( int argc, char** argv )
{
	options 		opt = options_init();
	
	if( options_parse( argc, argv, opt ) )
	{
		printf( "Error While Parsing Options: %s\n", options_get_error() );
		print_usage( stdout );
		return -1;
	}
	
	MagickWand* 		wand = NewMagickWand();
	
	size_t 			m_width, 
				m_height, 
				o_width, 
				o_height;
	
	options_get_dimensions( opt, &m_width, &m_height, &o_width, &o_height );
	
	sprite_sheet sheet = sheet_init();
	
	char* 			image 		= NULL;
	char* 			image_path	= options_input_path( opt );
	char 			path[1024];
	char			id_str[64];
	char 			name[64];

	while( ( image = options_next_image( opt ) ) != NULL )
	{
		sprintf( path, "%s/%s", image_path, image );
		sprite s;

		if( MagickReadImage( wand, path ) == MagickTrue )
		{
			image_id( image, id_str );
			sprite_init( &s, id_str, path, 0, 0, 0, 0 );
			sheet_add_sprite( sheet, &s );
		}
		else
		{
			fprintf( stderr, "Failed to Read Image at Path %s\n", path );
		}
	}

	MagickResetIterator( wand );

	while( MagickNextImage( wand ) != MagickFalse )
	{
		sprite* s = sheet_next_sprite( sheet );

		s->width 	= MagickGetImageWidth( wand );
		s->height	= MagickGetImageHeight( wand );
	}

	sheet_reset_iterator( sheet );

	DestroyMagickWand( wand );
	
	arrange( sheet, m_width, m_height, o_width, o_height );

	FILE* sheet_file	= fopen( options_sheet_path( opt ), "w" );
	FILE* image_file	= fopen( options_image_path( opt ), "w" );

	jpg_write( sheet, image_file, o_width, o_height, options_compression_quality( opt ) );
	write_xml( sheet, sheet_file );

	options_free( opt );

	fclose( image_file );
	fclose( sheet_file );

	return 0;
}