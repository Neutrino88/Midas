#include "application.h"

static SDL_Window* 	window;
static SDL_Surface* screen;

int init_window(const char* title, int width, int height) {
	
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return -1;
	
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	
	if ( screen == NULL ) return -1;
	screen = SDL_GetWindowSurface( window );
	
	return 0;	
}
