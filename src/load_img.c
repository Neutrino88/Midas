#include "SDL2/SDL.h"
#include "load_img.h"
#include "stdio.h"
#include "SDL2/SDL_image.h"

SDL_Surface *load_img(const char* filename);

SDL_Surface* images[IMGS_TOTAL];

SDL_Surface* load_img( const char* filename ) {
	/*The img that's loaded*/
	SDL_Surface* loadedImage;
	
	/*Initialize PNG loading*/
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return NULL;
	}	

	/*Load the img using SDL_image*/
	loadedImage = IMG_Load(filename);

	printf("loading img: %s\n", filename);		

	/*If the image loaded*/
	if( loadedImage == NULL ) {
		printf("Error opening image %s\n", filename);
	}

	/*Return the optimized image*/
	return loadedImage;
}

void load_imgs() {
	load_heroes_imgs();
	load_finish_imgs();
	load_backgr_imgs();
}

void load_heroes_imgs(){
	images[HEROES_GOLD_IMG] = load_img("img/heroes_gold.png");
	images[HEROES_NORMAL_IMG] = load_img("img/heroes_normal.png");
}

void load_finish_imgs(){
	images[FINISH_GOLD_IMG] = load_img("img/finish_gold.png");
	images[FINISH_NORMAL_IMG] = load_img("img/finish_normal.png");
}

void load_backgr_imgs(){
	images[BACKGROUND_IMG] = load_img("img/background.png");
}
