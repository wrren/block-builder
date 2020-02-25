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

#include <io/sheet_reader.h>

int read_bin( sprite_sheet sheet, FILE* file )
{
	if( file == NULL )
	{
	       return -1;
	}

	size_t sprite_count = 0;

	fread( &sprite_count, sizeof( size_t ), 1, file );

	if( sprite_count == 0 )
	{
		return 0;
	}

	sheet_expand_storage( sheet, sprite_count );
	sprite s;

	int length	= 0;
	char buffer[SPRITE_NAME_MAX];
	size_t x, y, width, height;
	
	while( sprite_count > 0 )
	{
		--sprite_count;

		fread( &length, sizeof( int ), 		1, file );
		fread( buffer, 	sizeof( char ), 	length, file );
		buffer[length] = '\0';
		fread( &x,	sizeof( size_t ),	1, file );
		fread( &y,	sizeof( size_t ),	1, file );
		fread( &width,	sizeof( size_t ),	1, file );
		fread( &height,	sizeof( size_t ),	1, file );

		sprite_init( &s, buffer, NULL, width, height, x, y );

		printf( "Got Sprite %s, ( %zu, %zu, %zux%zu )\n", s.name, s.x, s.y, s.width, s.height );

		sheet_add_sprite( sheet, &s );
	}

	return 0;
}