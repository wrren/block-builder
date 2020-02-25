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

#include <image/compositor.h>
#include <stdlib.h>
#include <stdio.h>

void resize( size_t* width, size_t* height, size_t max_width, size_t max_height )
{
	if( *width <= max_width && *height <= max_height )
	{
		return;
	}

	double max_ratio 	= ( ( double ) max_width ) / max_height;
	double ratio		= ( ( double ) *width ) / *height;
	double multiplier	= 1.0;

	// Input is wider than the out rectangle
	if( ratio >= max_ratio )
	{
		multiplier = ( ( double ) *width ) / max_width;
	}
	else
	{
		multiplier = ( ( double ) *height ) / max_height;
	}

	*width 	= *width / multiplier;
	*height = *height / multiplier;
}

void arrange( sprite_sheet sheet, size_t s_w, size_t s_h, size_t out_width, size_t out_height )
{
	sprite* sprite = NULL;
	size_t x = 0, y = 0, height = 0;
	size_t index = sheet_get_iterator( sheet );

	while( ( sprite = sheet_next_sprite( sheet ) ) != NULL )
	{
		resize( &( sprite->width ), &( sprite->height ), s_w, s_h );

		if( x + sprite->width > out_width )
		{
			y += height;
			x = height = 0;
		}

		if( y + sprite->height > out_height )
		{
			printf( "Unable to fit Sprite %s into Output Bounds, Removing from Sheet\n", sprite->name );
			sheet_remove_sprite( sheet );
			continue;
		}

		printf( "Arranged Sprite %s ( %zu, %zu, %zux%zu )\n", sprite->name, x, y, sprite->width, sprite->height );

		height = height < sprite->height ? sprite->height : height;

		sprite->x = x;
		sprite->y = y;

		x += sprite->width;
	}

	sheet_set_iterator( sheet, index );
}


