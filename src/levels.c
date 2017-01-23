#include "stdlib.h"
#include "malloc.h"

#include "levels.h"

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
		/* Reading info about heroes and finish */
		fread((void*)&(level->heroes.x), sizeof(short), 1, file);
		fread((void*)&(level->heroes.y), sizeof(short), 1, file);
		fread((void*)&(level->finish.x), sizeof(short), 1, file);
		fread((void*)&(level->finish.y), sizeof(short), 1, file);
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
		/* Writing info about heroes and finish */
		fwrite((void*)&(level->heroes.x), sizeof(short), 1, file);
		fwrite((void*)&(level->heroes.y), sizeof(short), 1, file);
		fwrite((void*)&(level->finish.x), sizeof(short), 1, file);
		fwrite((void*)&(level->finish.y), sizeof(short), 1, file);
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

Level_t* Create_lvl_0(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_0 error!\n");
		return NULL;
	}

	lvl->blocks_count = 11;

	lvl->heroes.x = 85;
	lvl->heroes.y = 100;
	lvl->finish.x = 40;
	lvl->finish.y = 100;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->h[i] = 57;
		lvl->w[i] = 57;
		lvl->y[i] = 200;
		
		if (0 == i)	lvl->x[0] = 65;
		else 		lvl->x[i] = 3 + lvl->w[i] + lvl->x[i-1];

		lvl->types[i] = NORM_TYPE;
	} 

	lvl->w[0] = lvl->w[0] + 28;
	lvl->x[0] = lvl->x[0] - 28;	

	lvl->types[8] = BLUE_TYPE;

	lvl->y[9] = lvl->y[0] + lvl->h[0];
	lvl->h[9] = 30;
	lvl->w[9] = lvl->w[0];
	lvl->x[9] = lvl->x[0];	

	return lvl;
}

Level_t* Create_lvl_1(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_1 error!\n");
		return NULL;
	}

	lvl->blocks_count = 10;

	lvl->heroes.x = 300;
	lvl->heroes.y = 161;
	lvl->finish.x = 400;
	lvl->finish.y = 100;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->h[i] = 57;
		lvl->w[i] = 57;
		lvl->y[i] = 200;
		
		if (0 == i)	lvl->x[0] = 60;
		else 		lvl->x[i] = 60 + lvl->x[i-1];

		lvl->types[i] = NORM_TYPE;
	} 

	lvl->types[8] = BLUE_TYPE;
	lvl->y[9] = lvl->y[0] - lvl->h[0];
	lvl->x[9] = lvl->x[0];	

	return lvl;
}

void Create_levels(char* filename){
	Levels_t* lvls 	= (Levels_t*)malloc(sizeof(Levels_t));
	
	if (NULL == lvls) {
		printf("Create_levels error!\n");
		return;
	}
	/* Allocating memory for lvls->lvls */
	lvls->lvls_count = 2;
	lvls->lvls = (Level_t**)calloc(sizeof(Level_t*),lvls->lvls_count);
	if (NULL == lvls->lvls){
		printf("Allocate memory for lvls->lvls failded (Create_levels)!\n");
		return;
	}

	lvls->lvls[0] = Create_lvl_0();
	lvls->lvls[1] = Create_lvl_1();

	/* Filling lvls data */
	
	Write_levels(lvls, filename);
}

void CleanUp_levels(Levels_t* lvls){
	int i;

	if (NULL == lvls) return;

	for (i = 0; i < lvls->lvls_count; ++i){
		free(lvls->lvls[i]->types);
		free(lvls->lvls[i]->x);
		free(lvls->lvls[i]->y);
		free(lvls->lvls[i]->h);
		free(lvls->lvls[i]->w);
		free(lvls->lvls[i]);

		lvls->lvls[i] = NULL;
	}

	free(lvls->lvls);
	free(lvls);
	lvls = NULL;
}