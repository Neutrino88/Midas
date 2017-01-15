#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "draw.h"

int Draw_image(SDL_Surface* dest_surface, SDL_Surface* src_surface, size_t x, size_t y){
    SDL_Rect dest_rect;

    if(dest_surface == NULL || src_surface == NULL) return -1;

	dest_rect.w = 0;
	dest_rect.h = 0;
    dest_rect.x = x;
    dest_rect.y = y;
 
    SDL_BlitSurface(src_surface, NULL, dest_surface, &dest_rect);
 
    return 0;
}

int Draw_rectangle(SDL_Surface* dest_surface, size_t block_type, size_t x, size_t y, size_t w, size_t h){
	SDL_Rect rect;

	if(dest_surface == NULL) return -1;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_FillRect(dest_surface, &rect, SDL_MapRGB(dest_surface->format, BORDER_COLOR_R, BORDER_COLOR_G, BORDER_COLOR_B));

	rect.x = x+1;
	rect.y = y+1;
	rect.w = w-2;
	rect.h = h-2;	
	
	if (GOLD_BLOCK == block_type)
		SDL_FillRect(dest_surface, &rect, SDL_MapRGB(dest_surface->format, GOLD_COLOR_R, GOLD_COLOR_G, GOLD_COLOR_B));
	if (GRAY_BLOCK == block_type)
		SDL_FillRect(dest_surface, &rect, SDL_MapRGB(dest_surface->format, GRAY_COLOR_R, GRAY_COLOR_G, GRAY_COLOR_B));
	if (BLUE_BLOCK == block_type)
		SDL_FillRect(dest_surface, &rect, SDL_MapRGB(dest_surface->format, BLUE_COLOR_R, BLUE_COLOR_G, BLUE_COLOR_B));

	dest_surface = NULL;
	return 0;
}

int Draw_image_in_every_pixel(SDL_Surface* dest_surface, SDL_Surface*	src_surface){
	int 			x;
	int 			screen_width;
	SDL_Rect 		dest_rect;

	if (dest_surface == NULL || src_surface == NULL) return -1;

	screen_width = dest_surface->w;

	dest_rect.y = 0;
	dest_rect.w = 0;
	dest_rect.h = 0;

	for (x = 0; x < screen_width; ++x){
	    dest_rect.x = x;
		SDL_BlitSurface(src_surface, NULL, dest_surface, &dest_rect);    
	}
 	
 	dest_surface = NULL;
 	src_surface  = NULL;
    return 0;
}