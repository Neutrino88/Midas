#include "SDL2/SDL.h"
#include "main.h"
#include "application.h"
#include "load_img.h"
#include "draw.h"
#include "phisics.h"

static int gameRunning;

int main() {
	Resource_init();
	Game_init();
	Main_loop();
	Clean_up();

	return 0;
}

static void Resource_init() {
	Init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	Load_imgs();
	/*Set_heads_imgs();*/
}

static void Game_init() {
	gameRunning = 1;
/*
	Draw_background();
	Draw_img(100, 50, Get_image(FINISH_GOLD_IMG));
	Draw_block(GRAY_BLOCK, 10, 10, 30, 30);
	Update_window();*/
}

static void Process_events() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
		if (event.type == SDL_QUIT){
			gameRunning = 0;
			break;
		}
		else if( event.type == SDL_KEYDOWN ){
			SDL_Keycode keycode = event.key.keysym.sym;

			if 		(keycode == SDLK_UP    	|| keycode == SDLK_w)	Key_up_event();
			else if (keycode == SDLK_LEFT  	|| keycode == SDLK_a)	Key_left_event();
            else if (keycode == SDLK_RIGHT 	|| keycode == SDLK_d)	Key_right_event();
            else if (keycode == SDLK_1 		|| keycode == SDLK_q)	Key_prev_level_event();
            else if (keycode == SDLK_3 		|| keycode == SDLK_e)	Key_next_level_event();
            else if (keycode == SDLK_2 		|| keycode == SDLK_r)	Key_restart_level_event();
			else {
				/*
				do nothing
				 */
			}
		}
}

static void Main_loop() {
	while( gameRunning ) {
		Process_events();
		Render();
	}	
}

static void Clean_up() {
	CleanUp_images();
	CleanUp_screen();
	CleanUp_window();

	SDL_Quit();
}

static void Key_up_event(void){
	Draw_background();
	Draw_img(100, 50, Get_image(FINISH_GOLD_IMG));

	Update_window();
}

static void Key_left_event(void){
	Draw_background();
	Draw_block(GRAY_BLOCK, 10, 10, 30, 30);

	Update_window();
}

static void Key_right_event(void){
	Draw_background();
	Draw_block(GOLD_BLOCK, 100, 300, 60, 40);

	Update_window();
}

static void Key_restart_level_event(void){

}

static void Key_next_level_event(void){

}

static void Key_prev_level_event(void){

}

static void Render(void){

}