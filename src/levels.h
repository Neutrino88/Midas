#ifndef _LEVELS_H_
	#define _LEVELS_H_
	
	enum{
		NORM_TYPE,
		GOLD_TYPE,
		BLUE_TYPE,
		TYPES_TOTAL
	};

	typedef struct {
		short x;
		short y;
	} Personal_t;

	typedef struct {		
		short *x;
		short *y;
		short *w;
		short *h;
		short *types;

		short blocks_count;
		Personal_t heroes;
		Personal_t finish;
	} Level_t;

	typedef struct {
		Level_t** lvls;
		short lvls_count;
	} Levels_t;

	Levels_t* 	Read_levels	(char* filename);
	int 		Write_levels(Levels_t* levels, char* filename);
	void 		CleanUp_levels(Levels_t* lvls);

	Level_t* 	Create_lvl_0(void);
	Level_t* 	Create_lvl_1(void);
	Level_t* 	Create_lvl_2(void);
	Level_t*	Create_lvl_3(void);
	Level_t* 	Create_lvl_4(void);
	void 		Create_levels(char* filename);
#endif