#include "SDL2/SDL.h"
#include "main.h"
#include "application.h"
#include "load_img.h"

int main() {
	resource_init();
	game_init();
	main_loop();
	clean_up();

	return 0;
}

static void resource_init() {
	init_window(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
	load_imgs();
}

static void game_init() {

}

static void main_loop() {

}

static void clean_up() {

}
