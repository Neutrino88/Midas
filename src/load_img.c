#include "SDL2/SDL.h"
#include "load_img.h"
#include "stdio.h"
#include "SDL2/SDL_image.h"
#include "application.h"

SDL_Surface* images[IMGS_TOTAL];

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

void Load_imgs(void) {
	Load_heroes_imgs();
	Load_finish_imgs();
	Load_backgr_imgs();
}

void Load_heroes_imgs(void){
	images[HEROES_GOLD_IMG] 	= Load_img("img/heroes_gold.png");
	images[HEROES_NORMAL_IMG] 	= Load_img("img/heroes_normal.png");
}

void Load_finish_imgs(void){
	images[FINISH_GOLD_IMG] 	= Load_img("img/finish_gold.png");
	images[FINISH_NORMAL_IMG] 	= Load_img("img/finish_normal.png");
}

void Load_backgr_imgs(void){
	images[BACKGROUND_IMG] 		= Load_img("img/background.png");
}

SDL_Surface* Get_image(int index){
	if (index < IMGS_TOTAL) return images[index];
	else 					return NULL;
}

void CleanUp_images(void){
	int i;
	for( i = 0; i < IMGS_TOTAL; ++i ) {
		if (NULL != images[i]) SDL_FreeSurface(images[i]);
		images[i] = NULL;
	}
}