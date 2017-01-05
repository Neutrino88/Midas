#ifndef _LOAD_IMG_H_
	#define _LOAD_IMG_H_

	enum SurfacesItems
	{
		HEROES_NORMAL_IMG,
		FINISH_NORMAL_IMG,
		HEROES_GOLD_IMG,
		FINISH_GOLD_IMG,
		BACKGROUND_IMG,
		IMGS_TOTAL
	};

	void load_imgs();
	void load_heroes_imgs();
	void load_finish_imgs();
	void load_backgr_imgs();
#endif
