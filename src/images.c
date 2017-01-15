#include "stdio.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "malloc.h"

#include "images.h"

SDL_Surface* Load_img( const char* filename ) {
	/*The img that's loaded*/
	SDL_Surface* loadedImage	= NULL;
	
	/*Initialize PNG loading*/
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return NULL;
	}	

	/*Load the img using SDL_image*/
	loadedImage = IMG_Load(filename);

	/*If the image loaded*/
	if( loadedImage == NULL )
		printf("Error opening image %s\n", filename);

	/*Return the optimized image*/
	return loadedImage;
}

void Load_heroes_imgs(SDL_Surface** images){
	images[HEROES_GOLD_IMG] 	= Load_img("img/heroes_gold.png");
	images[HEROES_NORMAL_IMG] 	= Load_img("img/heroes_normal.png");
}

void Load_finish_imgs(SDL_Surface** images){
	images[FINISH_GOLD_IMG] 	= Load_img("img/finish_gold.png");
	images[FINISH_NORMAL_IMG] 	= Load_img("img/finish_normal.png");
}

void Load_backgr_imgs(SDL_Surface** images){
	images[BACKGROUND_IMG] 		= Load_img("img/background.png");

	images[CLOUD_1_IMG] 		= Load_img("img/cloud_1.png");
	images[CLOUD_2_IMG] 		= Load_img("img/cloud_2.png");
	images[CLOUD_3_IMG] 		= Load_img("img/cloud_3.png");

}

SDL_Surface** Load_imgs(void){
	SDL_Surface** images = (SDL_Surface**)calloc(sizeof(SDL_Surface*), IMGS_TOTAL);
	if (NULL == images) return NULL;

	Load_heroes_imgs(images);
	Load_finish_imgs(images);
	Load_backgr_imgs(images);

	return images;
}

void CleanUp_imgs(SDL_Surface** images){
	int i;
	for(i = 0; i < IMGS_TOTAL; ++i) {
		if (NULL != images[i]) SDL_FreeSurface(images[i]);
	}

	free(images);
}