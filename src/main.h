#ifndef _MAIN_H_
	#define _MAIN_H_

	#define SCREEN_TITLE 	"Midas"
	#define SCREEN_WIDTH 	801
	#define SCREEN_HEIGHT 	534

	enum {
		GAME_STOPPING,
		GAME_RUNNING,
		GAME_OVER
	};	

	/* Initializes all resources*/
	static void Resource_init	(char* levels_file_path);
	/* Initializes all internal entities needed for the game at startup*/
	static void Game_init		(void);
	/* Perfoms a loop, updating and rendering*/
	static void Main_loop		(void);
	/* Frees all resources*/
	static void Clean_up		(void);

	static void Key_up_event	(void);
	static void Key_left_event	(void);
	static void Key_right_event	(void);
	static void Key_next_level_event(void);
	static void Key_prev_level_event(void);
	static void Key_restart_level_event	(void);
	static void Timer_event(void);

	static void Render(void);
#endif   
