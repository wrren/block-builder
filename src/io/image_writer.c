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

#include <io/image_writer.h>
#include <wand/magick_wand.h>

int jpg_write( sprite_sheet sheet, FILE* file, size_t width, size_t height, int quality )
{
	MagickWand* 	m_wand = NewMagickWand();
	MagickWand* 	o_wand = NewMagickWand();
	PixelWand*	p_wand = NewPixelWand();
	sprite*		sprite = NULL;

	PixelSetRed( 		p_wand, 1.0 );
        PixelSetGreen( 		p_wand, 1.0 );
        PixelSetBlue( 		p_wand, 1.0 );
        PixelSetOpacity( 	p_wand, 0.0 );
        
        printf( "Set Size: %d\n", MagickSetSize( o_wand, width, height ) );
       	printf( "Read Image: %d\n", MagickReadImage( o_wand, "xc:white" ) );
       	printf( "Set Format: %d\n", MagickSetImageFormat( o_wand, "JPEG" ) );
       	printf( "Set Image Resolution: %d\n", MagickSetImageResolution( o_wand, width, height ) );
       	printf( "Set Image Compression Quality: %d\n", MagickSetImageCompressionQuality( o_wand, quality ) );

	size_t index = sheet_get_iterator( sheet );

	while( ( sprite = sheet_next_sprite( sheet ) ) != NULL )
	{
		if( MagickReadImage( m_wand, sprite->file ) == MagickFalse )
		{
			fprintf( stderr, "Failed to Read Sprite at Path %s\n", sprite->file );
			sheet_remove_sprite( sheet );
		}
	}

	MagickResetIterator( m_wand );
	sheet_set_iterator( sheet, index );

	while( MagickNextImage( m_wand ) != MagickFalse )
	{
		sprite = sheet_next_sprite( sheet );
		MagickResizeImage( m_wand, sprite->width, sprite->height, LanczosFilter, 1.0 );
		MagickCompositeImage( o_wand, m_wand, OverCompositeOp, sprite->x, sprite->y );
	}

	int result = MagickWriteImageFile( o_wand, file );

	DestroyMagickWand( m_wand );
	DestroyPixelWand( p_wand );

	return result;
}