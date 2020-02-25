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

#include <image/compositor.h>
#include <catch.hpp>

TEST_CASE( "Compositor", "[image]" )
{
	SECTION( "Resizing" )
	{
		size_t width = 100, height = 100, max_width = 100, max_height = 100;
		resize( &width, &height, max_width, max_height );
		
		REQUIRE( width == 100 );
		REQUIRE( height == 100 );

		width 		= 400;
		height 		= 200;
		resize( &width, &height, max_width, max_height );

		REQUIRE( width == 100 );
		REQUIRE( height == 50 );

		width 		= 400;
		height 		= 200;
		max_width 	= 200;
		resize( &width, &height, max_width, max_height );

		REQUIRE( width == 200 );
		REQUIRE( height == 100 );

		width 		= 200;
		height 		= 400;
		max_height 	= 200;
		resize( &width, &height, max_width, max_height );

		REQUIRE( width == 100 );
		REQUIRE( height == 200 );
	}
}
