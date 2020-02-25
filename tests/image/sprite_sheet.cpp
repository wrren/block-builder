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

#include <image/sprite_sheet.h>
#include <catch.hpp>

TEST_CASE( "Sprite Sheet", "[image]" )
{
	sprite_sheet sheet = sheet_init();

	SECTION( "Add Sprite" )
	{
		sprite s;
		sprite_init( &s, "Test Sprite", NULL, 0, 0, 0, 0 );

		REQUIRE( sheet_sprite_count( sheet ) == 0 );
		sheet_add_sprite( sheet, &s );
		REQUIRE( sheet_sprite_count( sheet ) == 1 );

		sprite* sp = sheet_next_sprite( sheet );

		REQUIRE( strcmp( s.name, "Test Sprite" ) == 0 );
		REQUIRE( strcmp( s.name, sp->name ) == 0 );
		REQUIRE( s.width 	== sp->width );
		REQUIRE( s.height 	== sp->height );
		REQUIRE( s.x		== sp->x );
		REQUIRE( s.y		== sp->y );
	}

	SECTION( "Add Sprite with Offset" )
	{
		sheet_set_offset( sheet, 10, 20 );

		sprite s;
		sprite_init( &s, "Test Sprite", NULL, 0, 0, 0, 0 );

		REQUIRE( sheet_sprite_count( sheet ) == 0 );
		sheet_add_sprite( sheet, &s );
		REQUIRE( sheet_sprite_count( sheet ) == 1 );

		sprite* sp = sheet_next_sprite( sheet );

		REQUIRE( strcmp( s.name, "Test Sprite" ) == 0 );
		REQUIRE( strcmp( s.name, sp->name ) == 0 );
		REQUIRE( s.width 	== sp->width );
		REQUIRE( s.height 	== sp->height );
		REQUIRE( s.x		== sp->x - 10 );
		REQUIRE( s.y		== sp->y - 20 );
	}

	SECTION( "Apply Offset" )
	{
		sprite s;
		sprite_init( &s, "Test Sprite", NULL, 0, 0, 0, 0 );

		REQUIRE( sheet_sprite_count( sheet ) == 0 );
		sheet_add_sprite( sheet, &s );
		REQUIRE( sheet_sprite_count( sheet ) == 1 );

		sheet_apply_offset( sheet, 10, 20 );

		sprite* sp = sheet_next_sprite( sheet );
		
		REQUIRE( strcmp( s.name, "Test Sprite" ) == 0 );
		REQUIRE( strcmp( s.name, sp->name ) == 0 );
		REQUIRE( s.width 	== sp->width );
		REQUIRE( s.height 	== sp->height );
		REQUIRE( s.x		== sp->x - 10 );
		REQUIRE( s.y		== sp->y - 20 );
	}

	SECTION( "Concatenate" )
	{
		sprite s;
		sprite_init( &s, "Test Sprite", NULL, 0, 0, 0, 0 );
		sheet_add_sprite( sheet, &s );

		s.x = 100;
		sprite_sheet second = sheet_init();
		sheet_add_sprite( second, &s );

		sheet_concat( sheet, second );
		REQUIRE( sheet_sprite_count( sheet ) == 2 );

		sprite* sp = sheet_next_sprite( sheet );
		REQUIRE( sp->x == 0 );

		sp = sheet_next_sprite( sheet );
		REQUIRE( sp->x == 100 );
	}

	sheet_free( sheet );
}