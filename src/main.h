#ifndef _MAIN_H_
	#define _MAIN_H_

	#define SCREEN_TITLE 	"Midas"
	#define SCREEN_WIDTH 	640
	#define SCREEN_HEIGHT 	480

	/* Initializes all resources*/
	static void resource_init	( void );
	/* Initializes all internal entities needed for the game at startup*/
	static void game_init		( void );
	/* Perfoms a loop, updating and rendering*/
	static void main_loop		( void );
	/* Frees all resources*/
	static void clean_up		( void );
#endif   
