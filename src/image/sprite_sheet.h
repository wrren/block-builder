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

#ifndef UFA_SPRITE_SHEET_H
#define UFA_SPRITE_SHEET_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <image/sprite.h>
#include <string.h>

typedef struct _sprite_sheet* sprite_sheet;

/**
 *	Initialize a new sprite sheet
 */
sprite_sheet sheet_init( void );

/**
 *	Expand the sprite storage of the given sprite sheet so that it can hold at least 
 *	\a capacity sprites. This function will do nothing if the sheet can already contain
 *	at least \a capacity sprites.
 * @param sheet		Sprite Sheet
 * @param capacity	New Sheet Capacity.
 */
void sheet_expand_storage( sprite_sheet sheet, size_t capacity );

/**
 *	Set the X and Y offsets added to the positions of any sprites subsequently added
 *	to this sheet
 * @param sheet	Sprite Sheet
 * @param x	New X Offset
 * @param y	New Y Offset
 */
void sheet_set_offset( sprite_sheet sheet, size_t x, size_t y );

/**
 *	Apply an X and Y positional offset to all stored sprites
 * @param sheet	Sprite Sheet
 * @param x	X Offset
 * @param y	Y Offset
 */
void sheet_apply_offset( sprite_sheet sheet, size_t x, size_t y );

/**
 *	Concatenate the contents of one sprite sheet onto another
 * @param destination	Destination Sheet
 * @param source	Source Sheet
 */
void sheet_concat( sprite_sheet destination, sprite_sheet source );

/**
 *	Get the X offset being applied to added sprites for the given sheet
 * @param sheet	Sprite Sheet
 * @return	Current X Offset
 */
size_t sheet_x_offset( sprite_sheet sheet );

/**
 *	Get the Y offset being applied to added sprites for the given sheet
 * @param sheet	Sprite Sheet
 * @return	Current Y Offset
 */
size_t sheet_y_offset( sprite_sheet sheet );

/**
 *	Add a sprite to this sprite sheet. The current X and Y offset defined
 *	for the sheet will be applied immediately
 * @param sheet		Sprite Sheet
 * @param sprite	Sprite to be added
 */
void sheet_add_sprite( sprite_sheet sheet, sprite* sprite );

/**
 *	Get the next sprite in the sheet, this will increment the internal iterator
 * @param sheet	Sprite Sheet
 * @return	Sprite or NULL if the sheet contains no more sprites
 */
sprite* sheet_next_sprite( sprite_sheet sheet );

/**
 *	Remove the sprite at the current iterator position. After this operation, the
 *	iterator will be moved back one sprite in anticipation of the next call to 
 *	sheet_next_sprite
 * @param sheet	Sprite Sheet
 */
void sheet_remove_sprite( sprite_sheet sheet );

/**
 *	Get the current sprite iterator index
 * @param sheet	Sprite Sheet
 * @return	Sheet Sprite Iterator Index
 */
size_t sheet_get_iterator( sprite_sheet sheet );

/**
 *	Set the sheet iterator index. If the given index is greater than the number of 
 *	sprites in the sheet, no change will be made
 * @param sheet	Sprite Sheet
 * @param index	New iterator index
 */
void sheet_set_iterator( sprite_sheet sheet, size_t index );

/**
 *	Reset the sheet's internal sprite iterator to zero
 * @param sheet	Sprite Sheet
 */
void sheet_reset_iterator( sprite_sheet sheet );

/**
 *	Get the number of sprites held by this sprite sheet
 * @param sheet	Sprite Sheet
 * @return	Number of sprites in this sheet
 */
size_t sheet_sprite_count( sprite_sheet sheet );

/**
 *	Dump sheet info and contents to stdout
 * @param sheet	Sprite Sheet
 */
void sheet_dump( sprite_sheet sheet );

/**
 *	Free the specified sprite sheet
 * @param sheet	Sheet to be freed
 * @return	Sprite Sheet
 */
sprite_sheet sheet_free( sprite_sheet sheet );

#if defined (__cplusplus)
}
#endif

#endif // UFA_SPRITE_SHEET_H