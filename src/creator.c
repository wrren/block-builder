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

/**
 *	Main entry point to block-creator. Expects a set of command-line
 *	arguments indicating the location of the input images, the image file names
 *	to combine and the output path
 */
int create_block( 	const char* image_dir, 
			const char* sheet_path, 
			const char* image_path, 
			int bound_width, 
			int bound_height, 
			int out_width, 
			int out_height, 
			char** images,
			int image_count,
			int quality )
{
	MagickWand* 		wand = NewMagickWand();
		
	sprite_sheet sheet = sheet_init();
	
	char* 			image 		= NULL;
	char 			path[1024];
	char			id_str[64];
	char 			name[64];

	for( int i = 0; i < image_count; i++ )
	{
		image = images[i];
		sprintf( path, "%s/%s", image_dir, image );
		sprite s;

		if( MagickReadImage( wand, path ) )
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

	while( MagickNextImage( wand ) )
	{
		sprite* s 	= sheet_next_sprite( sheet );

		s->width 	= MagickGetImageWidth( wand );
		s->height	= MagickGetImageHeight( wand );
	}

	sheet_reset_iterator( sheet );

	DestroyMagickWand( wand );
	
	arrange( sheet, bound_width, bound_height, out_width, out_height );

	FILE* sheet_file	= fopen( sheet_path, "w" );
	FILE* image_file	= fopen( image_path, "w" );

	jpg_write( sheet, image_file, out_width, out_height, quality );
	write_xml( sheet, sheet_file );

	fclose( image_file );
	fclose( sheet_file );

	return 0;
}