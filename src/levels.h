#ifndef _LEVELS_H_
	#define _LEVELS_H_

	typedef struct {		
		short *x;
		short *y;
		short *w;
		short *h;
		short *types;

		short blocks_count;
	} Level_t;

	typedef struct {
		Level_t** lvls;
		short lvls_count;
	} Levels_t;

	Levels_t* 	Read_levels	(char* filename);
	int 		Write_levels(Levels_t* levels, char* filename);

	void 		Create_levels(char* filename);
	void 		CleanUp_levels(Levels_t* lvls);
#endif