#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#include "levels.h"

int levels_number;
Levels_t* levels = NULL;

Levels_t* Read_levels(char* filename){
    int i;
    Levels_t* levels = (Levels_t*)malloc(sizeof(Levels_t));

    /* Opening file for reading*/
    FILE* file = fopen(filename, "rb");
    if (NULL == file) {
		printf("Can't open '%s' for reading!\n", filename);
		return NULL;
	}

	/* Reading levels count */
	if (NULL == levels) return NULL;
	fread(&(levels->lvls_count), sizeof(levels->lvls_count), 1, file);	
	/* Allocating memory for levels*/
	levels->lvls = (Level_t**)calloc(sizeof(Level_t*), levels->lvls_count);
	if (NULL == levels->lvls) return NULL;
	/* Reading levels */
	for (i = 0; i < levels->lvls_count; ++i){
		/* Allocating memory for current level variable*/
		Level_t* level = (Level_t*)malloc(sizeof(Level_t));
		/* Reading blocks count*/
		fread( &(level->blocks_count), sizeof(level->blocks_count), 1, file);
		/* Allocating memory for x,y,w,h arrays */
		level->x = (int*)calloc(sizeof(int), level->blocks_count);
		level->y = (int*)calloc(sizeof(int), level->blocks_count);
		level->w = (int*)calloc(sizeof(int), level->blocks_count);
		level->h = (int*)calloc(sizeof(int), level->blocks_count);
		level->types = 	(int*)calloc(sizeof(int), level->blocks_count);

		if (NULL == level->x || NULL == level->y || NULL == level->w || NULL == level->h)
			return NULL;

		/* Reading x,y,w,h arrays */
		fread(level->x, sizeof(int) * level->blocks_count, 1, file);	
		fread(level->y, sizeof(int) * level->blocks_count, 1, file);
		fread(level->w, sizeof(int) * level->blocks_count, 1, file);
		fread(level->h, sizeof(int) * level->blocks_count, 1, file);
		fread(level->types, sizeof(int) * level->blocks_count, 1, file);
		/* Setting current level in levels variable */
		levels->lvls[i] = level;
	}

	/* Closing file*/
	fclose(file);
	/* Return levels variable */
	return levels;
}

int Write_levels(Levels_t* levels, char* filename){
	int i;
	FILE* file = NULL;
	if (NULL == levels || NULL == filename) return -1;

	/* Opening file for writing */
	file = fopen(filename, "wb");
    if (NULL == file) {
		printf("Can't open '%s' for writing!\n", filename);
		return -1;
	}

	fwrite(&(levels->lvls_count), sizeof(levels->lvls_count), 1, file);	
	/* Writing levels */
	for (i = 0; i < levels->lvls_count; ++i){
		/* Allocating memory for current level variable*/
		Level_t* level = levels->lvls[i];
		/* Writing blocks count*/
		fwrite( &(level->blocks_count), sizeof(level->blocks_count), 1, file);
		/* Writing x,y,w,h arrays */
		fwrite(level->x, sizeof(int) * level->blocks_count, 1, file);	
		fwrite(level->y, sizeof(int) * level->blocks_count, 1, file);
		fwrite(level->w, sizeof(int) * level->blocks_count, 1, file);
		fwrite(level->h, sizeof(int) * level->blocks_count, 1, file);
		fwrite(level->types, sizeof(int) * level->blocks_count, 1, file);
		/* Destroyed level pointer*/
		level = NULL;
	}

	return 0;
}

void Create_levels(void){
	int i;
	Levels_t* lvls 	= (Levels_t*)malloc(sizeof(Levels_t));
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvls || NULL == lvl) {
		printf("Create_levels failded!\n");
		return;
	}

	lvls->lvls_count = 1;
	/* Filling lvl data */
	lvl->blocks_count = 5;

	lvl->x = (int*)calloc(sizeof(int), lvl->blocks_count);
	lvl->y = (int*)calloc(sizeof(int), lvl->blocks_count);
	lvl->h = (int*)calloc(sizeof(int), lvl->blocks_count);
	lvl->w = (int*)calloc(sizeof(int), lvl->blocks_count);
	lvl->types = (int*)calloc(sizeof(int), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->h[i] = 60;
		lvl->w[i] = 60;
		lvl->y[i] = 200;
		
		if (0 == i)	lvl->x[0] = 60;
		else 		lvl->x[i] = 60 + lvl->x[i-1];

		lvl->types[i] = 1;
	} 

	lvls->lvls = (Level_t**)malloc(sizeof(Level_t*));
	if (NULL == lvls->lvls){
		printf("Allocate memory for lvls->lvls failded!\n");
		return;
	}
}