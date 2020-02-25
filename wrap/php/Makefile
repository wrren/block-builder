CREATOR_LIB_DIR=../../bin
CREATOR_LIB=creator
CC=gcc

all: block_creator.so

block_creator.so: php_block_creator.h block_creator_wrap.c ../../bin/libcreator.so
	$(CC) `php-config --includes` -fpic -c block_creator_wrap.c
	$(CC) -shared *.o -o block_creator.so -L$(CREATOR_LIB_DIR) -l$(CREATOR_LIB)

install: block_creator.so
	cp block_creator.so `php-config --extension-dir`
	cp ../../bin/libcreator.so /usr/local/lib/
