%module block_creator
%include "cpointer.i"
%{
	extern int create_block( const char* image_dir, const char* sheet, const char* image, int bound_width, int bound_height, int out_width, int out_height, char** images, int image_count, int quality );
%}

extern int create_block( const char* image_dir, const char* sheet, const char* image, int bound_width, int bound_height, int out_width, int out_height, char** images, int image_count, int quality );