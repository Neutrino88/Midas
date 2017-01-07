#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#include "levels.h"

Levels_t* Read_levels(char* filename){
    int i;
    Levels_t* levels = (Levels_t*)malloc(sizeof(Levels_t));

    /* Opening file */
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
		/* Reading level number and blocks count*/
		fread( &(level->lvl_number),   sizeof(level->lvl_number),   1, file);
		fread( &(level->blocks_count), sizeof(level->blocks_count), 1, file);
		/* Allocating memory for x,y,w,h arrays */
		level->x = (int*)calloc(sizeof(int), level->blocks_count);
		level->y = (int*)calloc(sizeof(int), level->blocks_count);
		level->w = (int*)calloc(sizeof(int), level->blocks_count);
		level->h = (int*)calloc(sizeof(int), level->blocks_count);

		if (NULL == level->x || NULL == level->y || NULL == level->w || NULL == level->h)
			return NULL;

		/* Reading x,y,w,h arrays */
		fread(level->x, sizeof(int) * level->blocks_count, 1, file);	
		fread(level->y, sizeof(int) * level->blocks_count, 1, file);
		fread(level->w, sizeof(int) * level->blocks_count, 1, file);
		fread(level->h, sizeof(int) * level->blocks_count, 1, file);
		/* Setting current level in levels variable */
		levels->lvls[i] = level;
	}

	/* Closing file*/
	fclose(file);
	/* Return levels variable */
	return levels;
}

int Write_levels(char* filename){
	return 0;
}
