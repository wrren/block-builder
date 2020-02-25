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

#ifndef UFA_SHEET_READER_H
#define UFA_SHEET_READER_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <image/sprite_sheet.h>
#include <stdio.h>

/**
 *	Type definition for functions that read sprite sheets from files
 * @param sheet	Sprite sheet to which read sprites may be added
 * @param file	File from which to read sheet data
 */
typedef int ( *sheet_reader )( sprite_sheet, FILE* );

/**
 *	Read sprite sheets from the given file in binary format
 */
int read_bin( sprite_sheet sheet, FILE* file );

#if defined (__cplusplus)
}
#endif

#endif // UFA_SHEET_READER_H