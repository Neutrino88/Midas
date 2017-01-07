#ifndef _PHISICS_H_
	#define _PHISICS_H_

	enum{
		HEROES,
		FINISH,
		PROBLEM,
		PERS_TOTAL
	};

	typedef struct {
		size_t type;
		size_t x;
		size_t y;
		size_t w;
		size_t h;
		float vx;
		float vy;
	} Coord_t;

void Set_heads_imgs(void);
Coord_t* Get_head_img(size_t index);

void Move_heroes_on_Ox(int step);

void CleanUp_heads(void);

#endif