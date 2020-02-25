/************************************************************************
 *									*
 * Upfront Analytics		   					*
 * Dragon Game Framework						*
 *									*
 * Author: 	Warren Kenny	<warren@ufa.ie>				*
 * 									*
 * Copyright 2014 Upfront Analytics. All rights reserved.		*
 *									*
 ************************************************************************/

#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <options/creator_options.h>

TEST_CASE( "Creator Options", "[options]" )
{
	options opt = options_init();
	size_t m_width, m_height, o_width, o_height;

	SECTION( "Initialize" )
	{
		REQUIRE( opt != NULL );
	}

	SECTION( "Parsing" )
	{
		const char* argv1[] = {	"mongle",
				 	"-i", "../images", 
					"--sheet", "sheet.bin", 
					"--image", "sheet.jpg", 
					"--max-width", "1",
					"--max-height", "2",
					"--out-width", "3",
					"--out-height", "4",
					"12345", NULL };

		REQUIRE( options_parse( 	sizeof( argv1 ) / sizeof( argv1[0] ) - 1,
						( char* const* ) argv1,
						opt ) == 0 );

		REQUIRE( options_image_count( opt ) == 1 );

		options_get_dimensions( opt, &m_width, &m_height, &o_width, &o_height );
		REQUIRE( m_width 	== 1 );
		REQUIRE( m_height 	== 2 );
		REQUIRE( o_width 	== 3 );
		REQUIRE( o_height 	== 4 );

		options_free( opt );

		opt = options_init();
		const char* argv2[] = {	"mongle",
				 	"--input-dir", "../images", 
					"--sheet", "sheet.bin",
					"12345", NULL };

		REQUIRE( options_parse( 	sizeof( argv2 ) / sizeof( argv2[0] ) - 1,
						( char* const* ) argv2,
						opt ) == -1 );

		options_free( opt );	

		opt = options_init();
		const char* argv3[] = {	"mongle",
				 	"--sheet", "sheet.bin", 
					"12345", NULL };

		REQUIRE( options_parse( 	sizeof( argv3 ) / sizeof( argv3[0] ) - 1,
						( char* const* ) argv3,
						opt ) == -1 );
	}

	options_free( opt );
}