#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

#include "levels.h"

int levels_number;
Levels_t* levels = NULL;

unsigned short ToOtherEndian(unsigned short num){
    return (num >> 8) | (num % 256 << 8);   
    /*
		05 00
		0000.0101 0000.0000	  LittleEndian

		0000.0000 0000.0101   BigEndian
    */
}

Levels_t* Read_levels(char* filename){
    int i;
    FILE* file = NULL;
    Levels_t* levels = NULL;

    /* Opening file for reading*/
    file = fopen(filename, "rb");
    if (NULL == file) {
		printf("Can't open '%s' for reading!\n", filename);
		return NULL;
	}

	/* Reading levels count */
	levels = (Levels_t*)malloc(sizeof(Levels_t));
	if (NULL == levels) return NULL;
		
	fread((void*)&(levels->lvls_count), sizeof(short), 1, file);	
	
	/* Allocating memory for levels*/
	levels->lvls = (Level_t**)malloc(sizeof(Level_t*) * levels->lvls_count);
	if (NULL == levels->lvls)return NULL;
	
	/* Reading levels */
	for (i = 0; i < levels->lvls_count; ++i){
		/* Allocating memory for current level variable*/
		Level_t* level = (Level_t*)malloc(sizeof(Level_t));
		if (NULL == level)return NULL;
		/* Reading blocks count*/
		fread((void*)&(level->blocks_count), sizeof(short), 1, file);
		/* Allocating memory for x,y,w,h arrays */
		level->x = 		(short*)malloc(sizeof(short) * level->blocks_count);
		level->y = 		(short*)malloc(sizeof(short) * level->blocks_count);
		level->w = 		(short*)malloc(sizeof(short) * level->blocks_count);
		level->h = 		(short*)malloc(sizeof(short) * level->blocks_count);
		level->types = 	(short*)malloc(sizeof(short) * level->blocks_count);
		if (NULL == level->x || NULL == level->y || NULL == level->w || NULL == level->h || NULL == level->types)return NULL;

		/* Reading x,y,w,h arrays */
		fread(level->x, sizeof(short), level->blocks_count, file);	
		fread(level->y, sizeof(short), level->blocks_count, file);
		fread(level->w, sizeof(short), level->blocks_count, file);
		fread(level->h, sizeof(short), level->blocks_count, file);
		fread(level->types, sizeof(short), level->blocks_count, file);

		/* Setting current level in levels variable */
		levels->lvls[i] = level;
		level = NULL;
	}

	/* Closing file*/
	fclose(file);
	/* Return levels variable */
	return levels;
}

int Write_levels(Levels_t* levels, char* filename){
	int i = 5;
	FILE* file = NULL;
	Level_t* level = NULL;
	if (NULL == levels || NULL == filename) return -1;

	/* Opening file for writing */
	file = fopen(filename, "wb");
    if (NULL == file) {
		printf("Can't open '%s' for writing!\n", filename);
		return -1;
	}

	fwrite((void*)&(levels->lvls_count), sizeof(short), 1, file);
	/* Writing levels */
	for (i = 0; i < levels->lvls_count; ++i){
		/* Allocating memory for current level variable*/
		level = levels->lvls[i];
		/* Writing blocks count*/
		fwrite((void*)&(level->blocks_count), sizeof(short), 1, file);
		/* Writing x,y,w,h arrays */
		fwrite((void*)level->x, sizeof(short), level->blocks_count, file);	
		fwrite((void*)level->y, sizeof(short), level->blocks_count, file);
		fwrite((void*)level->w, sizeof(short), level->blocks_count, file);
		fwrite((void*)level->h, sizeof(short), level->blocks_count, file);
		fwrite((void*)level->types, sizeof(short), level->blocks_count, file);
		/* Destroyed level pointer*/
		level = NULL;
	}
	/* Closing file*/
	fclose(file);
	return 0;
}

void Create_levels(char* filename){
	int i;

	Levels_t* lvls 	= (Levels_t*)malloc(sizeof(Levels_t));
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvls || NULL == lvl) {
		printf("Create_levels failded!\n");
		return;
	}

	/* Filling lvl data */
	lvl->blocks_count = 5;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->h[i] = 60;
		lvl->w[i] = 60;
		lvl->y[i] = 200;
		
		if (0 == i)	lvl->x[0] = 60;
		else 		lvl->x[i] = 60 + lvl->x[i-1];

		lvl->types[i] = 1;
	} 
	/* Allocating memory for lvls->lvls */
	lvls->lvls_count = 1;
	lvls->lvls = (Level_t**)malloc(sizeof(Level_t*) * lvls->lvls_count);
	if (NULL == lvls->lvls){
		printf("Allocate memory for lvls->lvls failded (Create_levels)!\n");
		return;
	}
	/* Filling lvls data */
	lvls->lvls[0] = lvl;

	printf("%s\n", Write_levels(lvls, filename) ? "Fail Write_levels" : "Access Write_levels");
}

void CleanUp_levels(Levels_t* lvls){
	int i;

	if (NULL == lvls) return;

	for (i = 0; i < lvls->lvls_count; ++i){

	}

}