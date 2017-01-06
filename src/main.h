#ifndef _MAIN_H_
	#define _MAIN_H_

	#define SCREEN_TITLE 	"Midas"
	#define SCREEN_WIDTH 	640
	#define SCREEN_HEIGHT 	480

	/* Initializes all resources*/
	static void Resource_init	( void );
	/* Initializes all internal entities needed for the game at startup*/
	static void Game_init		( void );
	/* Perfoms a loop, updating and rendering*/
	static void Main_loop		( void );
	/* Frees all resources*/
	static void Clean_up		( void );
#endif   
