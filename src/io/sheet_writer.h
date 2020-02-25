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

#ifndef UFA_SHEET_WRITER_H
#define UFA_SHEET_WRITER_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <image/sprite_sheet.h>
#include <stdio.h>

/**
 *	Prototype for sprite sheet writing function
 * @param sheet	Sheet to be written
 * @param file	File to which the sheet should be written
 * @return	0 on success. Error code on failure
 */
typedef int ( *sheet_writer )( sprite_sheet, FILE* );

/// Sheet writer that outputs in XML format 
int write_xml( sprite_sheet sheet, FILE* file );

/**
 *	Write the contents of the given sprite sheet in
 *	binary format
 */
int write_bin( sprite_sheet sheet, FILE* file );

#if defined (__cplusplus)
}
#endif

#endif // UFA_SHEET_WRITER_H