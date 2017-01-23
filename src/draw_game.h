#ifndef _DRAW_GAME_H_
	#define _DRAW_GAME_H_
	
	#include "SDL2/SDL.h"
	#include "stdio.h"
	#include "draw.h"
	#include "images.h"

	int 			Init_draw_game	(void);

	SDL_Surface* 	Get_image		(size_t index);

	int 			Draw_background	(void);
	int 			Draw_heroes		(size_t type, int x, int y);
	int 			Draw_finish		(size_t type, int x, int y);
	int 			Draw_block		(size_t type, int x, int y, size_t w, size_t h);
	int 			Draw_cloud		(size_t type, int x, int y);

	int 			Draw_you_won	(int x, int y);
	int 			Draw_you_lost	(int x, int y);

	void 			CleanUp_images	(void);
#endif