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

#include <image/sprite.h>
#include <string.h>

void sprite_init( sprite* sprite, char* name, char* file, size_t width, size_t height, size_t x, size_t y )
{
	if( name != NULL )
	{
		strncpy( sprite->name, name, SPRITE_NAME_MAX - 1 );
	}
	else
	{
		sprite->name[0] = '\0';
	}

	if( file != NULL )
	{
		strncpy( sprite->file, file, SPRITE_FILE_MAX - 1 );
	}
	else
	{
		sprite->file[0] = '\0';
	}

	sprite->width 	= width;
	sprite->height	= height;
	sprite->x	= x;
	sprite->y	= y;
}