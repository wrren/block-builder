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

#include <image/sprite_sheet.h>
#include <string.h>
#include <stdio.h>

struct _sprite_sheet
{
	/// Sprite Storage
	sprite* sprites;
	size_t 	sprite_capacity;
	size_t	sprite_count;
	size_t	sprite_index;

	/// X and Y Offsets
	size_t	x, y;
};

void sheet_expand_storage( sprite_sheet sheet, size_t capacity )
{
	if( capacity <= sheet->sprite_capacity )
	{
		return;
	}

	sprite* sprites = malloc( capacity * sizeof( sprite ) );

	if( sheet->sprite_count > 0 )
	{
		memcpy( sprites, sheet->sprites, sheet->sprite_count * sizeof( sprite ) );
	}
	
	sheet->sprites 		= sprites;
	sheet->sprite_capacity	= capacity;
}

sprite_sheet sheet_init( void )
{
	sprite_sheet sheet = malloc( sizeof( struct _sprite_sheet ) );
	sheet->sprites 		= NULL;
	sheet->sprite_capacity	= 0;
	sheet->sprite_count 	= 0;
	sheet->sprite_index	= 0;

	sheet->x = sheet->y	= 0;

	return sheet;
}

void sheet_set_offset( sprite_sheet sheet, size_t x, size_t y )
{
	sheet->x = x;
	sheet->y = y;
}

void sheet_apply_offset( sprite_sheet sheet, size_t x, size_t y )
{
	for( int i = 0; i < sheet->sprite_count; i++ )
	{
		sheet->sprites[i].x += x;
		sheet->sprites[i].y += y;
	}
}

void sheet_concat( sprite_sheet dst, sprite_sheet src )
{
	sprite* s;

	size_t index = sheet_get_iterator( src );
	sheet_reset_iterator( src );
	
	while( ( s = sheet_next_sprite( src ) ) != NULL )
	{
		sheet_add_sprite( dst, s );
	}
	
	sheet_set_iterator( src, index );
}

size_t sheet_x_offset( sprite_sheet sheet )
{
	return sheet->x;
}

size_t sheet_y_offset( sprite_sheet sheet )
{
	return sheet->y;
}

void sheet_add_sprite( sprite_sheet sheet, sprite* sprite )
{
	if( sheet->sprite_count == sheet->sprite_capacity )
	{
		sheet_expand_storage( sheet, sheet->sprite_capacity == 0 ? 1 : sheet->sprite_capacity * 2 );
	}

	sprite_init( 	&sheet->sprites[sheet->sprite_count++], 
			sprite->name, 
			sprite->file,
			sprite->width, sprite->height, 
			sprite->x + sheet->x, sprite->y + sheet->y );
}

sprite* sheet_next_sprite( sprite_sheet sheet )
{
	if( sheet->sprite_index < sheet->sprite_count )
	{
		return &( sheet->sprites[sheet->sprite_index++] );
	}

	return NULL;
}

void sheet_remove_sprite( sprite_sheet sheet )
{
	if( sheet->sprite_index > 0 )
	{
		--( sheet->sprite_index );
	}

	for( int i = sheet->sprite_index; i < ( sheet->sprite_count - 1 ); i++ )
	{
		sprite_init( 	&sheet->sprites[i], 
				sheet->sprites[i+1].name, 
				sheet->sprites[i+1].file,
				sheet->sprites[i+1].width, sheet->sprites[i+1].height, 
				sheet->sprites[i+1].x, sheet->sprites[i+1].y );
	}

	if( sheet->sprite_index < sheet->sprite_count )
	{
		--( sheet->sprite_count );
	}
}

size_t sheet_get_iterator( sprite_sheet sheet )
{
	return sheet->sprite_index;
}

void sheet_set_iterator( sprite_sheet sheet, size_t index )
{
	sheet->sprite_index = index >= sheet->sprite_count ? sheet->sprite_index : index;
}

void sheet_reset_iterator( sprite_sheet sheet )
{
	sheet->sprite_index = 0;
}

size_t sheet_sprite_count( sprite_sheet sheet )
{
	return sheet->sprite_count;
}

void sheet_dump( sprite_sheet sheet )
{
	size_t index = sheet_get_iterator( sheet );

	printf( "Sheet Sprite Count: %zu, Capacity: %zu, Sprites:\n", sheet->sprite_count, sheet->sprite_capacity );
	sprite* s;

	while( ( s = sheet_next_sprite( sheet ) ) != NULL )
	{
		printf( "\t%s ( %zu, %zu, %zux%zu )\n", s->name, s->x, s->y, s->width, s->height );
	}

	sheet_set_iterator( sheet , index );
}

sprite_sheet sheet_free( sprite_sheet sheet )
{
	if( sheet->sprites != NULL )
	{
		free( sheet->sprites );
	}

	free( sheet );

	return NULL;
}
