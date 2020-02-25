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

#include <options/builder_options.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

static char _error_buffer[200];

#define DEFAULT_OUT_WIDTH	512
#define DEFAULT_OUT_HEIGHT	512

struct _options
{
	// Array of Image IDs, count and iterator index
	char** 	blocks;
	int 	block_count;
	int 	block_idx;
	int 	quality;

	// Output Block Dimensions
	size_t	out_width, out_height;

	// Directory containing images
	char* 	input_dir;

	// Output Paths
	char* 	sheet_path;
	char* 	image_path;
};

options options_init( void )
{
	options opt = malloc( sizeof( struct _options ) );

	if( opt == NULL )
	{
		return NULL;
	}

	opt->block_count	= 0;
	opt->block_idx		= 0;
	opt->out_width		= DEFAULT_OUT_WIDTH;
	opt->out_height		= DEFAULT_OUT_HEIGHT;

	opt->input_dir = opt->sheet_path = opt->image_path = NULL;

	return opt;
}

options options_init_values( char* input_dir, char* image_path, char* sheet_path, char** blocks, int block_count )
{
	options opt = malloc( sizeof( struct _options ) );

	if( opt == NULL )
	{
		return NULL;
	}

	
	opt->blocks		= blocks;
	opt->block_count	= block_count;
	opt->block_idx		= 0;
	opt->input_dir 		= input_dir;
	opt->sheet_path 		= sheet_path;
	opt->image_path 	= image_path;

	return opt;
}

int options_parse( int argc, char* const* argv, options opt )
{
	int res = 0;
    	int area = -1, perimeter = -1, breadth = -1, length =-1;

	//Specifying the expected options
	//The two options l and b expect numbers as argument
	static struct option long_options[] = {
		{ "input-dir", 	required_argument, 0,  'i' },
		{ "sheet", 	required_argument, 0,  'x' },
		{ "image",    	required_argument, 0,  's' },
		{ "out-width", 	required_argument, 0,  'u' },
		{ "out-height", required_argument, 0,  'v' },
		{ "quality", 	required_argument, 0,  'q' },
		{ 0,           	0,                 0,  0   }
	};

	int long_index = 0;

	while( ( res = getopt_long( argc, argv, "i:x:s:u:v:", long_options, &long_index ) ) != -1 ) 
	{
	        switch( res ) 
	        {
	        case 'i':
	        	opt->input_dir = optarg;
                break;

		case 'x': 
			opt->sheet_path = optarg;
	        break;
	        
	        case 's': 
	        	opt->image_path = optarg;
	        break;

	        case 'u':
	        	opt->out_width = atoi( optarg );
	        break;

	        case 'v':
	        	opt->out_height = atoi( optarg );
	        break;

	        case 'q':
	        	opt->quality = atoi( optarg );
	        break;
	        
	        default:
	        	sprintf( _error_buffer, "Unknown Argument: %s", argv[long_index] );
	        	return -1;
        	}
        }

        if( opt->input_dir == NULL )
        {
        	sprintf( _error_buffer, "No Input Directory Argument Supplied" );
        	return -1;
        }
        if( opt->sheet_path == NULL )
        {
        	sprintf( _error_buffer, "No XML Output Path Argument Supplied" );
        	return -1;
        }
        if( opt->image_path == NULL )
        {
        	sprintf( _error_buffer, "No Sheet Output Path Argument Supplied" );
        	return -1;
        }
        if( opt->out_width == 0 || opt->out_height == 0 )
        {
        	sprintf( _error_buffer, "Output Dimensions Invalid" );
        	return -1;
        }
   	
        if( optind >= argc )
        {
        	sprintf( _error_buffer, "No Image IDs Supplied" );
        	return -1;
        }

        opt->blocks 		= malloc( ( argc - optind ) * sizeof( char* ) );
        opt->block_count 	= 0;
        
        int j = 0;
   	
   	for( int i = optind; i < argc; i++, j++ )
   	{
   		opt->blocks[j] = argv[i];
   		opt->block_count++;
   	}

	return 0;
}

char* options_next_block( options opt )
{
	if( opt->block_idx < opt->block_count )
	{
		return opt->blocks[opt->block_idx++];
	}

	return NULL;
}

void options_reset_block( options opt )
{
	opt->block_idx = 0;
}

int options_block_count( options opt )
{
	return opt->block_count;
}

int options_compression_quality( options opt )
{
	return opt->quality;
}

void options_get_dimensions( 	options opt,
				size_t* out_width, size_t* out_height )
{
	*out_width	= opt->out_width;
	*out_height	= opt->out_height;
}

char* options_input_path( options opt )
{
	return opt->input_dir;
}

char* options_sheet_path( options opt )
{
	return opt->sheet_path;
}

char* options_image_path( options opt )
{
	return opt->image_path;
}

char* options_get_error()
{
	return _error_buffer;
}

options options_free( options opt )
{
	if( opt != NULL )
	{
		free( opt );
	}
	return NULL;
}
