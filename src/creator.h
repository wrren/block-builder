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

#ifndef UFA_CREATOR_H
#define UFA_CREATOR_H

extern int create_block( 	const char* image_dir, 
				const char* sheet, 
				const char* image, 
				int bound_width, 
				int bound_height, 
				int out_width, 
				int out_height, 
				char** images,
				int image_count,
				int quality );

#endif // UFA_CREATOR_H