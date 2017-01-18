#ifndef _PHISICS_H_
	#define _PHISICS_H_

	enum{
		HEROES_PERS,
		FINISH_PERS,
		PROBLEM_PERS,
		PERS_TOTAL
	};

	enum{
		NORM_TYPE,
		GOLD_TYPE
	};

	typedef struct Coord_t{
		struct Coord_t* next;

		float vx;
		float vy;

		short type;
		short x;
		short y;
		short w;
		short h;
	} Coord_t;

void Set_heads_imgs(void);
Coord_t* Get_head_img(size_t index);

void Move_heroes_on_Ox(int step);

void CleanUp_heads(void);

#endif