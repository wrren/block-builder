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

#ifndef UFA_COMPOSITOR_H
#define UFA_COMPOSITOR_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <image/sprite_sheet.h>

/**
 *	Modify \a width and \a height so that they given within the given bounds
 *	while maintaining their aspect ratio
 * @param width		Input width to be modified
 * @param height	Input height to be modified
 * @param max_width	Maximum allowable width
 * @param max_height	Maximum allowable height
 */
void resize( size_t* width, size_t* height, size_t max_width, size_t max_height );

/**
 *	Arrange the sprites in the given sprite sheet so that they are optimally
 *	arranged within a bounding area described by \a out_width and \a out_height,
 *	with the maximum width and height of a sprite defined by \a sprite_width and
 *	\a sprite_height.
 */
void arrange( 	sprite_sheet sheet, 
		size_t sprite_width, size_t sprite_height,
		size_t out_width, size_t out_height );

#if defined (__cplusplus)
}
#endif

#endif // UFA_COMPOSITOR_H