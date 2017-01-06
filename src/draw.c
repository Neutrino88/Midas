#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "application.h"
#include "load_img.h"
#include "draw.h"

int Draw_img(size_t x, size_t y, SDL_Surface* src_surface){
    SDL_Rect dest_rect;

    dest_rect.x = x;
    dest_rect.y = y;
 
    if(Get_screen() == NULL || src_surface == NULL) return -1;
    SDL_BlitSurface(src_surface, NULL, Get_screen(), &dest_rect);
 
    return 0;
}

int Draw_block(size_t block_type, size_t x, size_t y, size_t w, size_t h){
	SDL_Rect rect;
	
	if(Get_screen() == NULL) return -1;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FillRect(Get_screen(), &rect, SDL_MapRGB(Get_screen()->format, BORDER_COLOR_R, BORDER_COLOR_G, BORDER_COLOR_B));

	rect.x = x+1;
	rect.y = y+1;
	rect.w = w-2;
	rect.h = h-2;	
	
	if (GOLD_BLOCK == block_type)
		SDL_FillRect(Get_screen(), &rect, SDL_MapRGB(Get_screen()->format, GOLD_COLOR_R, GOLD_COLOR_G, GOLD_COLOR_B));
	if (GRAY_BLOCK == block_type)
		SDL_FillRect(Get_screen(), &rect, SDL_MapRGB(Get_screen()->format, GRAY_COLOR_R, GRAY_COLOR_G, GRAY_COLOR_B));

	return 0;
}

int Draw_background(void){
	int x;
	int screen_width;
	SDL_Rect dest_rect;

	if (Get_screen() == NULL || Get_image(BACKGROUND_IMG) == NULL) return -1;

	screen_width = Get_screen()->w;

	for (x = 0; x < screen_width; ++x){
	    dest_rect.x = x;
		SDL_BlitSurface(Get_image(BACKGROUND_IMG), NULL, Get_screen(), &dest_rect);    
	}
 
    return 0;
}