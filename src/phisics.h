#ifndef _PHISICS_H_
	#define _PHISICS_H_

	typedef struct {
		size_t x;
		size_t y;
		size_t w;
		size_t h;
		int vx;
		int vy;
	} Coord;

void Set_heads_imgs(void);
Coord* Get_head_img(size_t index);

#endif