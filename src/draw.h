#ifndef _DRAW_H_
	#define _DRAW_H_
	
	enum {
		GOLD_BLOCK,
		GRAY_BLOCK,
		BLUE_BLOCK
	};

	#define GOLD_COLOR_R 255
	#define GOLD_COLOR_G 204
	#define GOLD_COLOR_B 51
	
	#define GRAY_COLOR_R 192
	#define GRAY_COLOR_G 192
	#define GRAY_COLOR_B 192

	#define BLUE_COLOR_R 30
	#define BLUE_COLOR_G 45
	#define BLUE_COLOR_B 110

	#define BORDER_COLOR_R 0
	#define BORDER_COLOR_G 0
	#define BORDER_COLOR_B 0

	int Draw_image_in_every_pixel	(SDL_Surface* dest_surface, SDL_Surface* src_surface);
	int Draw_image 					(SDL_Surface* dest_surface, SDL_Surface* src_surface, size_t x, size_t y);
	int Draw_rectangle				(SDL_Surface* dest_surface, size_t block_type, size_t x, size_t y, size_t w, size_t h);
#endif