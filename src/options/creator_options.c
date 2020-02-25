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

#include <options/creator_options.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

static char _error_buffer[200];

#define DEFAULT_MAX_WIDTH	128
#define DEFAULT_MAX_HEIGHT	128
#define DEFAULT_OUT_WIDTH	512
#define DEFAULT_OUT_HEIGHT	512

struct _options
{
	// Array of Image IDs, count and iterator index
	char** 	images;
	int 	image_count;
	int 	image_idx;
	int	quality;

	size_t 	max_width, max_height;
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

	opt->images 		= NULL;
	opt->image_count	= 0;
	opt->image_idx		= 0;
	opt->max_width		= DEFAULT_MAX_WIDTH;
	opt->max_height		= DEFAULT_MAX_HEIGHT;
	opt->out_width		= DEFAULT_OUT_WIDTH;
	opt->out_height		= DEFAULT_OUT_HEIGHT;

	opt->input_dir = opt->sheet_path = opt->image_path = NULL;

	return opt;
}

options options_init_values( char* input_dir, char* sheet_path, char* image_path, char** images, int image_count )
{
	options opt = malloc( sizeof( struct _options ) );

	if( opt == NULL )
	{
		return NULL;
	}

	opt->images 		= images;
	opt->image_count	= image_count;
	opt->image_idx		= 0;
	opt->input_dir 		= input_dir;
	opt->sheet_path 	= sheet_path;
	opt->image_path 	= image_path;

	return opt;
}

int options_parse( int argc, char* const* argv, options opt )
{
	extern int optind, opterr, optopt;
	int res = 0;
    	int area = -1, perimeter = -1, breadth = -1, length =-1;

	//Specifying the expected options
	//The two options l and b expect numbers as argument
	static struct option long_options[] = {
		{ "input-dir", 	required_argument, NULL,  'i' },
		{ "sheet", 	required_argument, NULL,  'o' },
		{ "image",    	required_argument, NULL,  's' },
		{ "max-width",	required_argument, NULL,  'w' },
		{ "max-height", required_argument, NULL,  'h' },
		{ "out-width", 	required_argument, NULL,  'u' },
		{ "out-height", required_argument, NULL,  'v' },
		{ "quality", 	required_argument, NULL,  'q' },
		{ NULL,        	0,                 NULL,  0   }
	};

	int long_index = 0;

	while( ( res = getopt_long( argc, argv, "i:o:s:w:h:u:v:", long_options, &long_index ) ) != EOF ) 
	{
	        switch( res ) 
	        {
	        case 'i':
	        	opt->input_dir = optarg;
                break;

		case 'o': 
			opt->sheet_path = optarg;
	        break;
	        
	        case 's': 
	        	opt->image_path = optarg;
	        break;

	        case 'w':
	        	opt->max_width = atoi( optarg );
	        break;

	        case 'h':
	        	opt->max_height = atoi( optarg );
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
        	sprintf( _error_buffer, "No Image Directory Argument Supplied" );
        	return -1;
        }
        if( opt->sheet_path == NULL )
        {
        	sprintf( _error_buffer, "No Sheet Output Path Argument Supplied" );
        	return -1;
        }
        if( opt->image_path == NULL )
        {
        	sprintf( _error_buffer, "No Image Output Path Argument Supplied" );
        	return -1;
        }
        if( opt->max_width == 0 || opt->max_height == 0 || opt->out_width == 0 || opt->out_height == 0 )
        {
        	sprintf( _error_buffer, "Image or Sheet Dimensions Invalid" );
        	return -1;
        }
   	
        if( optind >= argc )
        {
        	sprintf( _error_buffer, "No Image Paths Supplied" );
        	return -1;
        }

        opt->images 		= malloc( ( argc - optind ) * sizeof( char* ) );
        opt->image_count 	= 0;

   	for( int i = optind; i < argc; i++ )
   	{
   		opt->images[opt->image_count++] = argv[i];
   	}

	return 0;
}

char* options_next_image( options opt )
{
	if( opt->image_idx < opt->image_count )
	{
		return opt->images[opt->image_idx++];
	}

	return NULL;
}

void options_reset_image_id( options opt )
{
	opt->image_idx = 0;
}

int options_image_count( options opt )
{
	return opt->image_count;
}

int options_compression_quality( options opt )
{
	return opt->quality;
}

void options_get_dimensions( 	options opt, 
				size_t* max_width, size_t* max_height,
				size_t* out_width, size_t* out_height )
{
	*max_width 	= opt->max_width;
	*max_height	= opt->max_height;
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
		free( opt->images );
		free( opt );
	}
	return NULL;
}
