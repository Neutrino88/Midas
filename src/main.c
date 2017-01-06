#include "SDL2/SDL.h"
#include "main.h"
#include "application.h"
#include "load_img.h"
#include "draw.h"

int main() {
	Resource_init();
	Game_init();
	Main_loop();
	
	SDL_Delay( 2000 );
	Clean_up();

	return 0;
}

static void Resource_init() {
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_imgs();
}

static void Game_init() {
	Draw_img(100, 50, Get_image(FINISH_GOLD_IMG));
	Fill_rect(10, 10, 30, 30, 255, 0, 0);
	Update_window();
}

static void Main_loop() {

}

static void Clean_up() {
	CleanUp_images();
	CleanUp_window();

	SDL_Quit();
}