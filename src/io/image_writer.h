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

#ifndef UFA_IMAGE_WRITER_H
#define UFA_IMAGE_WRITER_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <image/sprite_sheet.h>
#include <stdio.h>

/**
 *	Prototype for sprite sheet image writing function
 * @param sheet		Sheet to be written
 * @param file		File to which the sheet should be written
 * @param width		Output Image Width
 * @param height	Output Image Height
 * @param quality	Image Compression Quality
 * @return		0 on success. Error code on failure
 */
typedef int ( *image_writer )( sprite_sheet, FILE*, size_t, size_t, int );

/**
 *	Write the contents of the given sprite sheet to the
 *	given output file as a composited jpg image
 */
int jpg_write( sprite_sheet sheet, FILE* file, size_t width, size_t height, int quality );

#if defined (__cplusplus)
}
#endif

#endif // UFA_IMAGE_WRITER_H