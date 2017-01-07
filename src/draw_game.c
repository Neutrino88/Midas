#include "draw_game.h"
#include "images.h"
#include "application.h"

SDL_Surface** images = NULL;

int Init_draw_game(void){
	images = Load_imgs();
	
	if (NULL == images) return -1;
	return 0;
}

SDL_Surface* Get_image(size_t index){
	if (index < IMGS_TOTAL) return images[index];
	else 					return NULL;
}

int Draw_heroes(size_t type, int x, int y){
	if 		(HEROES_NORMAL_IMG == type)
		return Draw_image(Get_screen(), Get_image(HEROES_NORMAL_IMG), x, y);
	else 
		return Draw_image(Get_screen(), Get_image(HEROES_GOLD_IMG),   x, y);
}

int Draw_finish(size_t type, int x, int y){
	if 		(FINISH_NORMAL_IMG == type)
		return Draw_image(Get_screen(), Get_image(FINISH_NORMAL_IMG), x, y);
	else 
		return Draw_image(Get_screen(), Get_image(FINISH_GOLD_IMG),   x, y);
}

int Draw_background(void){
	return Draw_image_in_every_pixel(Get_screen(), Get_image(BACKGROUND_IMG));
}

int Draw_block(size_t type, int x, int y, size_t w, size_t h){
	return Draw_rectangle(Get_screen(), type, x, y, w, h);
}