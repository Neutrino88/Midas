#include "application.h"

SDL_Window* 	window;
SDL_Surface* 	screen;

int Init_window(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return -1;
	
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
	if ( window == NULL ) return -1;
	screen = SDL_GetWindowSurface( window );
	
	return 0;	
}

SDL_Surface* Get_screen(void){
	return screen;
}

SDL_Window* Get_window(void){
	return window;
}

int Update_window(void){
	if (NULL == window) return -1;
	else 				return SDL_UpdateWindowSurface(window);
}

int Update_window_rect(int x, int y, unsigned int w, unsigned int h){
	SDL_Rect rect;
	
	if (window == NULL) return -1;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	return SDL_UpdateWindowSurfaceRects(window, &rect, 1);
}

void CleanUp_window(void){
	if (NULL != window) SDL_DestroyWindow(window);
	window = NULL;
}

void CleanUp_screen(void){
	if (NULL != screen) SDL_FreeSurface(screen);
	screen = NULL;
}