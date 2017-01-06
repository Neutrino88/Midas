#ifndef _APPLICATION_H_
	#define _APPLICATION_H_

	#include "SDL2/SDL.h"

	void Update_window(void);
	SDL_Surface* Get_screen(void);
	int Init_window( const char* title, int width, int height ); 

	void CleanUp_window(void);
	void CleanUp_screen(void);
#endif