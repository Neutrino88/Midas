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

void Update_window(void){
	SDL_UpdateWindowSurface(window);
}

void CleanUp_window(void){
	if (NULL != window) SDL_DestroyWindow(window);
	window = NULL;
}

void CleanUp_screen(void){
	if (NULL != screen) SDL_FreeSurface(screen);
	screen = NULL;
}