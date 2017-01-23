#include "application.h"
#include "draw_game.h"
#include "main.h"
#include "images.h"
#include "phisics.h"

static int game_status;
static Uint32 moveEventTime, 
	          lvlEventTime, 
	          phisicsEventTime,
	          cloudsEventTime;	/* program need this values for organization timers */

int main(int argc, char *argv[]) {	
	Resource_init((argc > 1) ? argv[1] : "levels");

	Game_init();
	Main_loop();
	Clean_up();

	return 0;
}

static void Resource_init(char* levels_file_path) {
	Init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);

	Init_draw_game();
	
	Init_phisics(levels_file_path);
	Restart_level(0);
}

static void Game_init(void) {
	moveEventTime 	 = SDL_GetTicks();
	lvlEventTime  	 = moveEventTime;
	phisicsEventTime = moveEventTime;
	cloudsEventTime = moveEventTime;

	game_status = GAME_RUNNING;
}

static void Process_events(void) {
	SDL_Event event;		/* Event handler */
	SDL_Keycode keycode;
	Uint32 curTime = SDL_GetTicks();
	const Uint8* curKey = SDL_GetKeyboardState( NULL );

	while( SDL_PollEvent( &event ) != 0 ) { 
		keycode = event.key.keysym.sym;

		if(event.type == SDL_QUIT) { 
			game_status = GAME_OVER;
			return;
		} 

		if (curTime - lvlEventTime >= 200){
			lvlEventTime = curTime;

			if (keycode == SDLK_1 		|| keycode == SDLK_q)	Key_prev_level_event();	
	        if (keycode == SDLK_3 		|| keycode == SDLK_e)	Key_next_level_event();	
	        if (keycode == SDLK_2 		|| keycode == SDLK_r)	Key_restart_level_event();
	    }
	}

	if ((GAME_RUNNING == game_status) && (curTime - moveEventTime >= 20)){
		moveEventTime = curTime;

		if (curKey[SDL_SCANCODE_UP]		|| curKey[SDL_SCANCODE_W])	Key_up_event();
		if (curKey[SDL_SCANCODE_LEFT]	|| curKey[SDL_SCANCODE_A])	Key_left_event();
		if (curKey[SDL_SCANCODE_RIGHT]	|| curKey[SDL_SCANCODE_D])	Key_right_event();
	}

	if (GAME_RUNNING == game_status && (curTime - phisicsEventTime >= 23)){
		phisicsEventTime = curTime;		

		Timer_event();
	}

	if (GAME_RUNNING == game_status && (curTime - cloudsEventTime >= 40)){
		cloudsEventTime = curTime;

		MoveClouds(!0, !0, !0);
	}
}

static void Main_loop(void) {
	while(GAME_OVER != game_status) {
		Process_events();
		
		if (GAME_RUNNING == game_status)
			Render();
	}	
}

static void Clean_up(void) {
	CleanUp_images();
	CleanUp_screen();
	CleanUp_window();
	CleanUp_heads();

	SDL_Quit();
}

static void Key_up_event(void){
	Jump_heroes_on_oy();
}

static void Key_left_event(void){
	Move_heroes_on_ox(-5);
	Collision_detection();
}

static void Key_right_event(void){
	Move_heroes_on_ox(5);
	Collision_detection();
}

static void Key_restart_level_event(void){
	Restart_level(-1);
	game_status = GAME_RUNNING;
}

static void Key_next_level_event(void){
	Restart_level(-2);
	game_status = GAME_RUNNING;
}

static void Key_prev_level_event(void){
	Restart_level(-3);
	game_status = GAME_RUNNING;
}

static void Timer_event(void){
	Phisics_update();
	Collision_detection();
}

static void Render(void){
	Update_screen();
	Update_window_rect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

	/* if (finish is gold) then game stopping */
	if (Game_over())	
		game_status = GAME_STOPPING;
}