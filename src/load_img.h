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

	void Load_imgs(void);
	void Load_heroes_imgs(void);
	void Load_finish_imgs(void);
	void Load_backgr_imgs(void);

	SDL_Surface* Get_image(int index);
	void CleanUp_images(void);
#endif
