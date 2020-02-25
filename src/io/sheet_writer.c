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

#include <io/sheet_writer.h>
#include <string.h>

int write_xml( sprite_sheet sheet, FILE* file )
{
	if( file == NULL )
	{
	       return -1;
	}

	sheet_reset_iterator( sheet );

	fprintf( file, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n" );
	fprintf( file, "<spritesheet>\n" );

	sprite* s = NULL;

	while( ( s = sheet_next_sprite( sheet ) ) != NULL )
	{
	       fprintf( file, "\t<sprite>\n" );

	       fprintf( file, "\t\t<name>%s</name>\n",         s->name );
	       fprintf( file, "\t\t<left>%zu</left>\n",         s->x );
	       fprintf( file, "\t\t<top>%zu</top>\n",           s->y );
	       fprintf( file, "\t\t<width>%zu</width>\n",       s->width );
	       fprintf( file, "\t\t<height>%zu</height>\n",      s->height );

	       fprintf( file, "\t</sprite>\n" );
	}

	fprintf( file, "</spritesheet>" );

	sheet_reset_iterator( sheet );

	return 0;
}

int write_bin( sprite_sheet sheet, FILE* file )
{
	size_t sprite_count = sheet_sprite_count( sheet );

	if( file == NULL || sprite_count == 0 )
	{
		return 0;
	}

	sprite* s 	= NULL;
	int length	= 0;

	sheet_reset_iterator( sheet );

	fwrite( &sprite_count, sizeof( size_t ), 1, file );

	while( ( s = sheet_next_sprite( sheet ) ) != NULL )
	{
		length = strlen( s->name );
		
		fwrite( &length, 	sizeof( int ), 		1, 	file );
		fwrite( s->name, 	sizeof( char ), 	length, file );
		fwrite( &s->x, 		sizeof( size_t ), 	1, 	file );
		fwrite( &s->y, 		sizeof( size_t ), 	1, 	file );
		fwrite( &s->width, 	sizeof( size_t ), 	1, 	file );
		fwrite( &s->height,	sizeof( size_t ),	1,	file );
	}

	sheet_reset_iterator( sheet );

	return 0;
}
