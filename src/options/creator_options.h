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

#ifndef UFA_CREATOR_OPTIONS_H
#define UFA_CREATOR_OPTIONS_H

#if defined (__cplusplus)
extern "C" {
#endif

#include <stdlib.h>

typedef struct _options* options;

/**
 *	Initialize an options handle
 * @return	Options Handle
 */
options options_init( void );

/**
 *	Initialize an options handle with the specified values
 * @param input_dir	Directory from which to read input images and sheets
 * @param sheet_path	Output Sheet Path
 * @param image_path	Output Image Path
 * @param images	Array of Image Paths
 * @param image_count	Number of Image Paths in \a images
 * @return		Options Handle
 */
options options_init_values( char* input_dir, char* sheet_path, char* image_path, char** images, int image_count );

/**
 *	Parse a set of program arguments to generate an options structure
 * @param argc		Number of program arguments
 * @param argv		Array of argument strings
 * @param opt		Output options handle
 * @param error		Output error string
 * @return		0 on success. !0 on error.
 */
int options_parse( int argc, char* const* argv, options opt );

/**
 *	Get the next image in the image list
 * @param opt	Options Handle
 * @return	Image path or -1 if the end of the list has been reached
 */
char* options_next_image( options opt );

/**
 *	Reset the option image list iterator
 * @param opt	Options Handle
 */
void options_reset_image( options opt );

/**
 *	Get the sheet output dimensions and max dimensions for a single image specified by 
 *	these options
 * @param opt			Options
 * @param max_width[out]	Max width of a single image
 * @param max_height[out]	Max Height of a single image
 * @param out_width[out]	Sheet Output Width
 * @param out_height[out]	Sheet Output Height
 */
void options_get_dimensions( 	options opt, 
				size_t* max_width, size_t* max_height,
				size_t* out_width, size_t* out_height );

/**
 *	Get the number of image IDs specified in this option handle
 * @param opt	Options Handle
 * @return	Number of specified Image IDs
 */
int options_image_count( options opt );

/**
 *	Get the image input path
 * @param opt	Options Handle
 * @return	Options Image Input Path
 */
char* options_input_path( options opt );

/**
 *	Get the image compression quality for image writing
 * @param opt	Options Handle
 * @return	Options Compression Quality
 */
int options_compression_quality( options opt );

/**
 *	Get the sheet mapping output path
 * @param opt	Options Handle
 * @return	Options Sheet Mapping Output Path
 */
char* options_sheet_path( options opt );

/**
 *	Get the sheet image output path
 * @param opt	Options Handle
 * @return	Options Sheet Output Path
 */
char* options_image_path( options opt );

/**
 *	Get the last error raised
 * @return	String describing the last error raised
 */
char* options_get_error();

/**
 *	Free an options handle
 * @param opt	Options Handle
 * @return	NULL
 */
options options_free( options opt );

#if defined (__cplusplus)
}
#endif

#endif // UFA_CREATOR_OPTIONS_H