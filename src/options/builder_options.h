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

#ifndef UFA_BUILDER_OPTIONS_H
#define UFA_BUILDER_OPTIONS_H

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
 * @param input_dir	Directory from which to read input blocks
 * @param sheet_path	Output Image Sheet Path
 * @param xml_path	Output XML Path
 * @param blocks	List of input block names
 * @param block_count	Number of block names in \a blocks
 * @return		Options Handle
 */
options options_init_values( char* input_dir, char* sheet_path, char* xml_path, char** blocks, int block_count );

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
 *	Get the next block name
 * @param opt	Options Handle
 * @return	Block name or NULL if all blocks have been read
 */
char* options_next_block( options opt );

/**
 *	Reset the option block list iterator
 * @param opt	Options Handle
 */
void options_reset_block( options opt );

/**
 *	Get the number of blocks specified in this option handle
 * @param opt	Options Handle
 * @return	Number of specified blocks
 */
int options_block_count( options opt );

/**
 *	Get the image compression quality for image writing
 * @param opt	Options Handle
 * @return	Options Compression Quality
 */
int options_compression_quality( options opt );

/**
 *	Get the output block dimensions
 * @param opt			Options Handle
 * @param out_width[out]	Output Block Width
 * @param out_height[out]	Output Block Height
 */
void options_get_dimensions( options opt, size_t* out_width, size_t* out_height );

/**
 *	Get the block input path
 * @param opt	Options Handle
 * @return	Options Block Input Path
 */
char* options_input_path( options opt );

/**
 *	Get the xml mapping output path
 * @param opt	Options Handle
 * @return	Options XML Output Path
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

#endif // UFA_BUILDER_OPTIONS_H