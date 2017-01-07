#ifndef _APPLICATION_H_
	#define _APPLICATION_H_

	#include "SDL2/SDL.h"

	int Update_window(void);
	int Update_window_rect(int x, int y, unsigned int w, unsigned int h);

	SDL_Surface* Get_screen(void);
	SDL_Window*  Get_window(void);

	int Init_window( const char* title, int width, int height ); 

	void CleanUp_window(void);
	void CleanUp_screen(void);
#endif