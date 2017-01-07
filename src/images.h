#ifndef _LOAD_IMG_H_
	#define _LOAD_IMG_H_
	
	#include "SDL2/SDL.h"

	enum SurfacesItems
	{
		HEROES_NORMAL_IMG,
		FINISH_NORMAL_IMG,
		HEROES_GOLD_IMG,
		FINISH_GOLD_IMG,
		BACKGROUND_IMG,
		IMGS_TOTAL
	};

	SDL_Surface* 	Load_img 		( const char* filename );
	
	void 			Load_heroes_imgs(SDL_Surface** images);
	void 			Load_finish_imgs(SDL_Surface** images);
	void 			Load_backgr_imgs(SDL_Surface** images);
	
	SDL_Surface** 	Load_imgs 		(void);
	void 			CleanUp_imgs 	(SDL_Surface** images);
#endif
