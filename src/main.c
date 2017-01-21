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
	
	Init_phisics("blabla");
}

static void Game_init() {
	game_status = GAME_RUNNING;
}

static void Process_events() {
	SDL_Event event;	/* Event handler */
	const Uint8* curKey = SDL_GetKeyboardState( NULL );

	while( SDL_PollEvent( &event ) != 0 ) { 
		if(event.type == SDL_QUIT) { 
			game_status = GAME_STOPPING;
			return;
		} 
	}	

	if (curKey[SDL_SCANCODE_UP]		|| curKey[SDL_SCANCODE_W])	Key_up_event();
	if (curKey[SDL_SCANCODE_LEFT]	|| curKey[SDL_SCANCODE_A])	Key_left_event();
    if (curKey[SDL_SCANCODE_RIGHT]	|| curKey[SDL_SCANCODE_D])	Key_right_event();
    if (curKey[SDL_SCANCODE_1]		|| curKey[SDL_SCANCODE_Q])	Key_prev_level_event();
    if (curKey[SDL_SCANCODE_3]		|| curKey[SDL_SCANCODE_E])	Key_next_level_event();
    if (curKey[SDL_SCANCODE_2]		|| curKey[SDL_SCANCODE_R])	Key_restart_level_event();
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

}

static void Key_left_event(void){
	Move_heroes_on_ox(-1);

	Collision_detection();

}

static void Key_right_event(void){
	Move_heroes_on_ox(1);

	Collision_detection();

}

static void Key_restart_level_event(void){

}

static void Key_next_level_event(void){

}

static void Key_prev_level_event(void){

}

static void Render(void){
	Update_screen();
	Update_window();
}