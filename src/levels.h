#ifndef _LEVELS_H_
	#define _LEVELS_H_

	typedef struct {		
		int *x;
		int *y;
		int *w;
		int *h;
		int *types;

		size_t blocks_count;
	} Level_t;

	typedef struct {
		Level_t** lvls;
		size_t 	 lvls_count;
	} Levels_t;

	Levels_t* 	Read_levels	(char* filename);
	int 		Write_levels(Levels_t* levels, char* filename);

	void 		Create_levels(void);
#endif