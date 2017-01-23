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

	lvl->blocks_count = 22;

	lvl->heroes.x = 25;
	lvl->heroes.y = 150;
	lvl->finish.x = 695;
	lvl->finish.y = 150;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < 12; ++i){
		lvl->h[i] = 56;
		lvl->w[i] = 56;
		lvl->y[i] = 250;
		lvl->types[i] = NORM_TYPE;

		if 		(0 == i)	lvl->x[i] = 10;
		else if (8 == i)	{
			lvl->w[i] = 3 * lvl->w[i];
			lvl->x[i] = lvl->w[i-1] + lvl->x[i-1];	
		}
		else lvl->x[i] = lvl->w[i-1] + lvl->x[i-1];
	} 

	for (i = 12; i < lvl->blocks_count; ++i){
		lvl->h[i] = 56;
		lvl->w[i] = 56;
		lvl->y[i] = 250 + lvl->h[i-12];
		lvl->types[i] = NORM_TYPE;
	} 

	lvl->x[12] = lvl->x[0];
	lvl->x[13] = lvl->x[2];
	lvl->x[14] = lvl->x[4];
	lvl->x[15] = lvl->x[6];
	lvl->x[16] = lvl->x[8];
	lvl->x[17] = lvl->x[8] + lvl->w[17];
	lvl->x[18] = lvl->x[8] + 2*lvl->w[17];
	lvl->x[19] = lvl->x[9];
	lvl->x[20] = lvl->x[10];
	lvl->x[21] = lvl->x[11];

	lvl->types[8] = BLUE_TYPE;	

	return lvl;
}

Level_t* Create_lvl_1(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_1 error!\n");
		return NULL;
	}

	lvl->blocks_count = 15;

	lvl->heroes.x = 65;
	lvl->heroes.y = 150;
	lvl->finish.x = 25;
	lvl->finish.y = 150;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->h[i] = 56;
		lvl->w[i] = 56;
		lvl->y[i] = 250;
		lvl->types[i] = NORM_TYPE;
		
		if (0 == i)	{
			lvl->x[i] = 10;
			lvl->w[i] = 2*lvl->w[i];
		}
		else 		
			lvl->x[i] = lvl->x[i-1] + lvl->w[i-1];
	} 

	lvl->h[11]		= 28;
	lvl->y[11]		= lvl->y[0] + lvl->h[11];
	lvl->types[11] 	= BLUE_TYPE;

	lvl->h[13] 		= 57;
	lvl->w[13] 		= lvl->w[11];
	lvl->x[13]		= lvl->x[11];
	lvl->y[13] 		= lvl->y[11] + lvl->h[11];
	lvl->types[13]  = NORM_TYPE;

	lvl->h[14] 		= 28;
	lvl->w[14] 		= lvl->w[0];
	lvl->x[14]		= lvl->x[0];
	lvl->y[14] 		= 500;
	lvl->types[14]  = NORM_TYPE;

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