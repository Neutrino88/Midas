#include "application.h"
#include "draw_game.h"
#include "main.h"
#include "images.h"
#include "phisics.h"

static int game_status;

int main(int argc, char *argv[]) {	
	Resource_init((argc > 1) ? argv[0] : "levels");

	Game_init();
	Main_loop();
	Clean_up();

	return 0;
}

static void Resource_init(char* levels_file_path) {
	Init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

	Init_draw_game();

	printf("%i\n",Init_phisics("blabla"));
}

static void Game_init() {
	game_status = GAME_RUNNING;
}

static void Process_events() {
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
		if (event.type == SDL_QUIT){
			game_status = GAME_STOPPING;
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
	Draw_background();
	Update_window();

	while(GAME_RUNNING == game_status) {
		Process_events();
		Render();
	}	
}

static void Clean_up() {
	CleanUp_images();
	CleanUp_screen();
	CleanUp_window();

	/*CleanUp_heads();
	CleanUp_levels();*/

	SDL_Quit();
}

static void Key_up_event(void){
	Draw_background();
	Draw_heroes(HEROES_NORMAL_IMG, 10, 40);
	Update_window_rect(10, 40, 50, 50);
}

static void Key_left_event(void){
	Draw_background();
	Draw_block(GOLD_BLOCK, 30, 200, 50, 40);
	Update_window_rect(30, 200, 50, 40);
}

static void Key_right_event(void){
	Draw_background();
	Draw_block(GRAY_BLOCK, 300, 400, 50, 40);
	Update_window_rect(300, 400, 50, 40);
}

static void Key_restart_level_event(void){

}

static void Key_next_level_event(void){
/*	Levels_t* lvls = NULL;

	Create_levels("blabla");
	lvls =  Read_levels("blabla");
	if (NULL == lvls) printf("%s\n", "Error of Read_levels");
	else{
		CleanUp_levels(lvls);
	}*/

}

static void Key_prev_level_event(void){

}

static void Render(void){
	Update_window_rect(30, 200, 50, 40);
	Update_window_rect(300, 400, 50, 40);
	Update_window_rect(10, 40, 50, 50);
}