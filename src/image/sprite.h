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

#ifndef UFA_SPRITE_H
#define UFA_SPRITE_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <stdlib.h>

#define SPRITE_NAME_MAX	256
#define SPRITE_FILE_MAX	256

/**
 *	Basic image information
 */
typedef struct 
{
	char 	name[SPRITE_NAME_MAX];	// Sprite Name
	char 	file[SPRITE_FILE_MAX];	// Sprite Path
	size_t	width;			// Sprite Pixel Width
	size_t	height;			// Sprite Pixel Height
	size_t 	x;			// Sprite Top-Left X Position
	size_t	y;			// Sprite Top-Left Y Position
} sprite;

/**
 *	Convenience initialization function
 */
void sprite_init( sprite* sprite, char* name, char* file, size_t width, size_t height, size_t x, size_t y );

#if defined (__cplusplus)
}
#endif

#endif // UFA_SPRITE_H