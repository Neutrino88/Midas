#include "stdio.h"
#include "malloc.h"

#include "phisics.h"
#include "draw_game.h"
#include "levels.h"

Coord_t* head_imgs[PERS_TOTAL];
Coord_t* head_blocks;

Levels_t* levels;
short	  level_number;

int Init_phisics(char* levelsFileName){
	/* Reading levels */
	levels = Read_levels(levelsFileName);
	if (levels == NULL) return -1;
	
	level_number = 0;
	/* Setting head_img values */
	head_imgs[HEROES_PERS] = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[HEROES_PERS]->vx   = 0;
	head_imgs[HEROES_PERS]->vy   = 0;
	head_imgs[HEROES_PERS]->x    = levels->lvls[level_number]->heroes.x;
	head_imgs[HEROES_PERS]->y    = levels->lvls[level_number]->heroes.y;;
	head_imgs[HEROES_PERS]->w    = Get_image(HEROES_GOLD_IMG)->w;
	head_imgs[HEROES_PERS]->h    = Get_image(HEROES_GOLD_IMG)->h;
	head_imgs[HEROES_PERS]->type = GOLD_TYPE;

	head_imgs[FINISH_PERS]  = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[FINISH_PERS]->vx   = 0;
	head_imgs[FINISH_PERS]->vy   = 0;
	head_imgs[FINISH_PERS]->x    = levels->lvls[level_number]->finish.x;
	head_imgs[FINISH_PERS]->y    = levels->lvls[level_number]->finish.y;;
	head_imgs[FINISH_PERS]->w    = Get_image(FINISH_NORMAL_IMG)->w;
	head_imgs[FINISH_PERS]->h    = Get_image(FINISH_NORMAL_IMG)->h;
	head_imgs[FINISH_PERS]->type = GOLD_TYPE;

	head_imgs[PROBLEM_PERS] = (Coord_t*)malloc(sizeof(Coord_t));


	/* Setting head_blocks values */

	return 0;
}



Coord_t* Get_head_img(size_t index){
	if (index < PERS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

void Move_heroes_on_Ox(int step){

}

void Restart_level(int l){

}

void CleanUp_heads(void){
	int i;
	for (i = 0; i < PERS_TOTAL; ++i){
		free(head_imgs[i]);
		head_imgs[i] = NULL;
	}
	
	if (NULL != head_blocks)
		free(head_blocks);
}
