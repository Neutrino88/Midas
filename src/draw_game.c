#include "draw_game.h"
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
	if (HEROES_NORMAL_IMG == type)
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

int Draw_cloud(size_t type, int x, int y){
	if (type == CLOUD_1_IMG)
		return Draw_image(Get_screen(), Get_image(CLOUD_1_IMG), x, y);
	else if (type == CLOUD_2_IMG)
		return Draw_image(Get_screen(), Get_image(CLOUD_2_IMG), x, y);
	else
		return Draw_image(Get_screen(), Get_image(CLOUD_3_IMG), x, y);
}

int Draw_you_won(int x, int y){
	return Draw_image(Get_screen(), Get_you_won_label(), x, y);
}

int Draw_you_lost(int x, int y){
	return Draw_image(Get_screen(), Get_you_lost_label(), x, y);
}

int Draw_control_keys(int x, int y){
	return Draw_image(Get_screen(), Get_image(CONTROL_KEYS_IMG), x, y);
}

void CleanUp_images(void){
	CleanUp_imgs(images);
}
