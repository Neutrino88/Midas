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
	int i;
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

Level_t* Create_lvl_2(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_2 error!\n");
		return NULL;
	}

	lvl->blocks_count = 39;

	lvl->heroes.x = 389;
	lvl->heroes.y = 250;
	lvl->finish.x = 140;
	lvl->finish.y = 250;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->h[i] = 56;
		lvl->w[i] = 56;
		lvl->types[i] = NORM_TYPE;
	}
	/* 1 line */
	for (i = 0; i < 10; ++i){
		lvl->y[i] = 400;
		
		if (0 == i)	lvl->x[i] = 125;
		else 		lvl->x[i] = lvl->x[i-1] + lvl->w[i-1];
	} 
	/* 2 line */
	for (i = 10; i < 20; ++i){
		lvl->y[i] = 344;
		
		if (10 == i) lvl->x[i] = lvl->x[0];
		else 		 lvl->x[i] = lvl->x[i-1] + lvl->w[i-1];
	} 
	/* 3 line */
	for (i = 20; i < 30; ++i){
		if (20 == i) lvl->x[i] = lvl->x[0];
		else 		 lvl->x[i] = lvl->x[i-1] + lvl->w[i-1];

		lvl->y[i] = 288;		
	} 
	/* 4 line */
	for (i = 30; i < 38; ++i){
		if (30 == i) lvl->x[i] = lvl->x[1];
		else 		 lvl->x[i] = lvl->x[i-1] + lvl->w[i-1];	

		lvl->y[i] = 232;	
	} 
	/* 2 levitation blocks */
	lvl->y[20] = 35;
	lvl->h[20] = 73;

	lvl->y[29] = 35;
	lvl->h[29] = 73;
	/* (5 line) 2 big central blocks */
	lvl->y[23] = lvl->y[30] - lvl->h[30];
	lvl->w[23] = 112;

	lvl->y[25] = lvl->y[23];
	lvl->w[25] = lvl->w[23];
	/* 2 blocks which to the left and to the right big blocks */
	lvl->y[24] = lvl->y[23];
	lvl->x[24] = lvl->x[23] - lvl->w[24];

	lvl->y[26] = lvl->y[23];
	lvl->x[26] = lvl->x[25] + lvl->w[25];
	/* 6 line */
	lvl->y[32] = lvl->y[23] - lvl->h[23];
	lvl->y[33] = lvl->y[32];
	lvl->y[34] = lvl->y[32];
	lvl->y[35] = lvl->y[32];
	/* blue block */
	lvl->w[38] = 40;
	lvl->h[38] = 39;
	lvl->y[38] = lvl->y[19] - lvl->h[38];
	lvl->x[38] = lvl->x[19] + 8;
	lvl->types[38] = BLUE_TYPE;
	return lvl;
}

Level_t* Create_lvl_3(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_3 error!\n");
		return NULL;
	}

	lvl->blocks_count = 11;

	lvl->heroes.x = 100;
	lvl->heroes.y = 100;
	lvl->finish.x = 600;
	lvl->finish.y = 300;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 28;
		lvl->h[i] = 28;	
	}

	lvl->x[0] = 25;
	lvl->y[0] = 480;

	lvl->x[1] = lvl->x[0];
	lvl->h[1] = 280;
	lvl->y[1] = lvl->y[0] - lvl->h[1];
	
	lvl->x[2] = lvl->x[0];
	lvl->y[2] = lvl->y[1] - lvl->h[2];
	lvl->w[2] = 230;

	lvl->x[3] = lvl->x[2] + lvl->w[2] - lvl->w[3];
	lvl->y[3] = lvl->y[1];
	lvl->h[3] = 60;

	lvl->x[4] = lvl->x[3] - lvl->w[4];
	lvl->y[4] = lvl->y[3] + lvl->h[3] - lvl->h[4];
	lvl->types[4] = BLUE_TYPE;

	lvl->w[5] = 120;
	lvl->x[5] = lvl->x[4] + 2*lvl->w[4] - lvl->w[5];
	lvl->y[5] = lvl->y[4] + lvl->h[4];

	lvl->w[6] = 148;
	lvl->x[6] = lvl->x[3];
	lvl->y[6] = lvl->y[5] + lvl->h[5];

	lvl->w[7] = 148;
	lvl->x[7] = lvl->x[6] + lvl->w[6] - 28;
	lvl->y[7] = lvl->y[6] + lvl->h[6];

	lvl->w[8] = 120;
	lvl->x[8] = lvl->x[7] + lvl->w[7] - 28;
	lvl->y[8] = lvl->y[7] + lvl->h[7];

	lvl->w[9] = 56;
	lvl->h[9] = 84;
	lvl->x[9] = lvl->x[8] + lvl->w[8];
	lvl->y[9] = lvl->y[8] + lvl->h[8];

	lvl->w[10] = lvl->w[8] + lvl->w[9];
	lvl->x[10] = lvl->x[8];
	lvl->y[10] = lvl->y[9] + lvl->h[9];

	return lvl;
}

Level_t* Create_lvl_4(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_4 error!\n");
		return NULL;
	}

	lvl->blocks_count = 14;

	lvl->heroes.x = 80;
	lvl->heroes.y = 300;
	lvl->finish.x = 685;
	lvl->finish.y = 370;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < lvl->blocks_count; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 60;
		lvl->h[i] = 28;	
	}

	lvl->x[0] = 60;
	lvl->y[0] = 430;
	lvl->h[0] = 56;

	lvl->x[1] = lvl->x[0];
	lvl->y[1] = lvl->y[0] - lvl->h[1];
	
	lvl->x[2] = lvl->x[1] + lvl->w[1] + 60;
	lvl->y[2] = lvl->y[1];

	lvl->x[3] = lvl->x[2] + lvl->w[2];
	lvl->y[3] = lvl->y[2];

	lvl->x[4] = lvl->x[3] + lvl->w[3] + 120;
	lvl->y[4] = lvl->y[3];	

	lvl->x[5] = lvl->x[4] + lvl->w[4] + 60;
	lvl->y[5] = lvl->y[4] - 56;

	lvl->x[6] = lvl->x[4];
	lvl->y[6] = lvl->y[4] - 120;		

	lvl->x[7] = lvl->x[5] + 110;
	lvl->y[7] = lvl->y[0] + lvl->h[0] - lvl->h[7];		

	lvl->x[8] = lvl->x[3] + lvl->w[3];
	lvl->y[8] = lvl->y[6] - 2*lvl->h[8];

	lvl->x[9] = lvl->x[2];
	lvl->y[9] = lvl->y[8] + lvl->h[8];

	lvl->x[10] = lvl->x[9] - lvl->w[10];
	lvl->y[10] = lvl->y[9] - lvl->h[10];

	lvl->x[11] = lvl->x[0];
	lvl->y[11] = lvl->y[10] - 2*lvl->h[10];

	lvl->x[12] = lvl->x[9];
	lvl->y[12] = lvl->y[11] - 2*lvl->h[11];

	lvl->x[13] = lvl->x[8];
	lvl->y[13] = lvl->y[12] - 2*lvl->h[12];
	lvl->h[13] = 14;
	lvl->w[13] = 1.9 * lvl->w[13];
	lvl->types[13] = BLUE_TYPE;

	return lvl;
}

Level_t* Create_lvl_5(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_5 error!\n");
		return NULL;
	}

	lvl->blocks_count = 27;

	lvl->heroes.x = 362;
	lvl->heroes.y = 50;
	lvl->finish.x = 30;
	lvl->finish.y = 50;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < 10; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 56;
		lvl->h[i] = 56;	
	}

	lvl->x[0] = 15;
	lvl->y[0] = 150;

	lvl->x[1] = lvl->x[0] + lvl->w[0];
	lvl->y[1] = lvl->y[0];

	lvl->x[2] = lvl->x[1] + lvl->w[1];
	lvl->y[2] = lvl->y[1];
	
	lvl->x[3] = lvl->x[2] + lvl->w[2];
	lvl->y[3] = lvl->y[2];

	lvl->x[4] = lvl->x[0];
	lvl->y[4] = lvl->y[0] + lvl->h[0];

	lvl->x[5] = lvl->x[1];
	lvl->y[5] = lvl->y[4];

	lvl->x[6] = lvl->x[2];
	lvl->y[6] = lvl->y[4];

	lvl->x[7] = lvl->x[0];
	lvl->y[7] = lvl->y[4] + lvl->h[4];

	lvl->x[8] = lvl->x[1];
	lvl->y[8] = lvl->y[7];

	lvl->x[9] = lvl->x[0];
	lvl->y[9] = lvl->y[7] + lvl->h[7];

	for (i = 10; i < lvl->blocks_count; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 28;
		lvl->h[i] = 28;	
	}

	lvl->x[10] = lvl->x[0];
	lvl->y[10] = 480;
	lvl->w[10] = 4 * lvl->w[0];
	lvl->h[10] = 20;

	lvl->x[11] = lvl->x[0];
	lvl->y[11] = lvl->y[10] + lvl->h[10];
	lvl->w[11] = 4 * lvl->w[0];
	lvl->h[11] = lvl->h[10];

	lvl->x[12] = lvl->x[10] + lvl->w[10] + 80;
	lvl->y[12] = lvl->y[10];
	lvl->w[12] = lvl->w[0] + 60;
	lvl->h[12] = lvl->h[10];

	lvl->x[13] = lvl->x[12];
	lvl->y[13] = lvl->y[11];
	lvl->w[13] = lvl->w[12];
	lvl->h[13] = lvl->h[11];

	lvl->x[14] = lvl->x[13];
	lvl->y[14] = 40;
	lvl->h[14] = 6 * lvl->h[0];	
	lvl->w[14] = 20;

	lvl->w[15] = 20;
	lvl->x[15] = lvl->x[13] + lvl->w[13] - lvl->w[15];
	lvl->y[15] = 40;
	lvl->h[15] = 6 * lvl->h[0];	

	lvl->x[16] = lvl->x[14] + lvl->w[14] + 24;
	lvl->y[16] = lvl->y[13] - 65;

	lvl->x[17] = lvl->x[16] + 130;
	lvl->y[17] = lvl->y[16];

	lvl->x[18] = lvl->x[17] + lvl->w[17];
	lvl->y[18] = lvl->y[17];



	lvl->x[19] = lvl->x[18];
	lvl->y[19] = lvl->y[18] - 120;

	lvl->x[20] = lvl->x[19];
	lvl->y[20] = lvl->y[19] - 120;

	lvl->x[21] = lvl->x[20] + 130;
	lvl->y[21] = lvl->y[18] - 60;

	lvl->x[22] = lvl->x[21];
	lvl->y[22] = lvl->y[21] - 120;

	lvl->x[23] = lvl->x[22];
	lvl->y[23] = lvl->y[22] - 120;

	lvl->x[24] = lvl->x[22] + 100;
	lvl->y[24] = lvl->y[23] - 20;	
	lvl->w[24] = lvl->w[24] - 10;
	lvl->h[24] = lvl->h[24] - 10;
	lvl->types[24] = BLUE_TYPE;

	lvl->x[25] = lvl->x[24] - 12;
	lvl->y[25] = lvl->y[24] + lvl->h[24];	
	lvl->w[25] = lvl->w[24] + 24;
	lvl->h[25] = 8;

	lvl->x[26] = lvl->x[25] + 10;
	lvl->y[26] = lvl->y[25] + lvl->h[25];	
	lvl->w[26] = lvl->w[25] - 20;
	lvl->h[26] = 8;

	
	return lvl;
}

Level_t* Create_lvl_6(void){
	int i;
	Level_t*  lvl 	= (Level_t*) malloc(sizeof(Level_t));

	if (NULL == lvl) {
		printf("Create_lvl_6 error!\n");
		return NULL;
	}

	lvl->blocks_count = 61;

	lvl->heroes.x = 75;
	lvl->heroes.y = 50;
	lvl->finish.x = 670;
	lvl->finish.y = 400;

	lvl->x =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->y =     (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->h = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->w = 	 (short*)calloc(sizeof(short), lvl->blocks_count);
	lvl->types = (short*)calloc(sizeof(short), lvl->blocks_count);

	for (i = 0; i < 11; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 60;
		lvl->h[i] = 20;

		if 		(i == 0) 	lvl->x[i] = 60;
		else if (i % 2 == 0)lvl->x[i] = lvl->x[i-2] + 2*lvl->w[i-2];
		else 				lvl->x[i] = lvl->x[i-1];

		if 		(i == 0) 	lvl->y[i] = 100;
		else if (i == 1)	lvl->y[i] = lvl->y[i-1] + lvl->h[i-1];
		else 				lvl->y[i] = lvl->y[i-2];
	}

	for (i = 11; i < 16; ++i){
		lvl->types[i] = BLUE_TYPE;
		lvl->w[i] = 60;
		lvl->h[i] = 40;
		lvl->x[i] = lvl->x[(i-11)*2] + lvl->w[(i-11)*2];
		lvl->y[i] = lvl->y[0];
	}

	for (i = 16; i < 26; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 60;
		lvl->h[i] = 20;

		if 		(i == 16) 	lvl->x[i] = lvl->x[10];
		else if (i == 17)	lvl->x[i] = lvl->x[i-1] - 2*lvl->w[i-1];
		else if (i == 27)	lvl->x[i] = lvl->x[i-2] -   lvl->w[i-2];
		else if (i % 2 == 1)lvl->x[i] = lvl->x[i-2] - 2*lvl->w[i-2];
		else 				lvl->x[i] = lvl->x[i-1];

		if 		(i == 16) 	lvl->y[i] = lvl->y[11] + lvl->h[11] + 150;
		else if (i % 2 == 1)lvl->y[i] = lvl->y[i-1] - lvl->h[i-1];
		else 				lvl->y[i] = lvl->y[i-1] + lvl->h[i-1];
	}

	for (i = 26; i < 31; ++i){
		lvl->types[i] = BLUE_TYPE;
		lvl->w[i] = 60;
		lvl->h[i] = 40;
		lvl->x[i] = lvl->x[i - 15];
		lvl->y[i] = lvl->y[16] - lvl->h[16];
	}

	lvl->types[31] = NORM_TYPE;
	lvl->w[31] = 60;
	lvl->h[31] = 20;
	lvl->x[31] = lvl->x[0];
	lvl->y[31] = lvl->y[26] + lvl->h[11] + 150;

	for (i = 32; i < 44; ++i){
		lvl->types[i] = NORM_TYPE;
		lvl->w[i] = 20;
		lvl->h[i] = 24;
		lvl->y[i] = lvl->y[31] - lvl->h[31];

		if (32 == i)lvl->x[i] = lvl->x[31]  +   lvl->w[31];
		else 		lvl->x[i] = lvl->x[i-1] + 2*lvl->w[i-1];
	}

	for (i = 44; i < 56; ++i){
		lvl->types[i] = BLUE_TYPE;
		lvl->w[i] = 20;
		lvl->h[i] = 20;
		lvl->y[i] = lvl->y[31] - lvl->h[31] + 4;

		lvl->x[i] = lvl->x[i-12] + lvl->w[i-12];
	}
		
	lvl->types[56] = NORM_TYPE;
	lvl->w[56] = 10;
	lvl->h[56] = (lvl->y[55] + lvl->h[55]) - (lvl->y[26] + lvl->h[26]);
	lvl->x[56] = lvl->x[55] + lvl->w[55];
	lvl->y[56] = lvl->y[26] + lvl->h[26];

	lvl->types[57] = NORM_TYPE;
	lvl->w[57] = 10;
	lvl->h[57] = lvl->h[56];
	lvl->x[57] = lvl->x[56] + lvl->w[56];
	lvl->y[57] = lvl->y[56];

	lvl->types[58] = NORM_TYPE;
	lvl->w[58] = 100;
	lvl->h[58] = 20;
	lvl->x[58] = lvl->x[57] + lvl->w[57];
	lvl->y[58] = lvl->y[44];

	lvl->types[59] = BLUE_TYPE;
	lvl->w[59] = 10;
	lvl->h[59] = (lvl->y[31] + lvl->h[31]) - lvl->y[0];
	lvl->x[59] = lvl->x[0] - lvl->w[59];
	lvl->y[59] = lvl->y[0];

	lvl->types[60] = lvl->types[59];
	lvl->w[60] = lvl->w[59];
	lvl->h[60] = lvl->h[59] - 16;
	lvl->x[60] = lvl->x[10] + lvl->w[10];
	lvl->y[60] = lvl->y[59];

	return lvl;
}

void Create_levels(char* filename){
	Levels_t* lvls 	= (Levels_t*)malloc(sizeof(Levels_t));
	
	if (NULL == lvls) {
		printf("Create_levels error!\n");
		return;
	}
	/* Allocating memory for lvls->lvls */
	lvls->lvls_count = 7;
	lvls->lvls = (Level_t**)calloc(sizeof(Level_t*),lvls->lvls_count);
	if (NULL == lvls->lvls){
		printf("Allocate memory for lvls->lvls failded (Create_levels)!\n");
		return;
	}

	lvls->lvls[0] = Create_lvl_0();
	lvls->lvls[1] = Create_lvl_1();
	lvls->lvls[2] = Create_lvl_2();
	lvls->lvls[3] = Create_lvl_3();
	lvls->lvls[4] = Create_lvl_4();
	lvls->lvls[5] = Create_lvl_5();
	lvls->lvls[6] = Create_lvl_6();

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