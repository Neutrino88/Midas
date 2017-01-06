#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "application.h"

int Draw_img(size_t x, size_t y, SDL_Surface* src_surface){
    SDL_Rect dest_rect;

    dest_rect.x = x;
    dest_rect.y = y;
 
    if(Get_screen() == NULL || src_surface == NULL) return -1;
    SDL_BlitSurface(src_surface, NULL, Get_screen(), &dest_rect);
 
    return 0;
}

void Fill_rect(size_t x, size_t y, size_t w, size_t h, size_t red, size_t green, size_t blue){
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_FillRect(Get_screen(), &rect, SDL_MapRGB(Get_screen()->format, red, green, blue));
}