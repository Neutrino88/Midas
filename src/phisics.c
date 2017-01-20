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
	int i;
	/* Reading levels */
	Create_levels("blabla");
	levels = Read_levels(levelsFileName);
	if (levels == NULL) return -1;
	
	level_number = 0;
	/* Setting head_img values */
	head_imgs[HEROES_PERS] = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[HEROES_PERS]->next = NULL;
	head_imgs[HEROES_PERS]->vx   = 0;
	head_imgs[HEROES_PERS]->vy   = 0;
	head_imgs[HEROES_PERS]->x    = levels->lvls[level_number]->heroes.x;
	head_imgs[HEROES_PERS]->y    = levels->lvls[level_number]->heroes.y;;
	head_imgs[HEROES_PERS]->w    = Get_image(HEROES_GOLD_IMG)->w;
	head_imgs[HEROES_PERS]->h    = Get_image(HEROES_GOLD_IMG)->h;
	head_imgs[HEROES_PERS]->type = GOLD_TYPE;

	head_imgs[FINISH_PERS]  = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[FINISH_PERS]->next = head_imgs[HEROES_PERS];
	head_imgs[FINISH_PERS]->vx   = 0;
	head_imgs[FINISH_PERS]->vy   = 0;
	head_imgs[FINISH_PERS]->x    = levels->lvls[level_number]->finish.x;
	head_imgs[FINISH_PERS]->y    = levels->lvls[level_number]->finish.y;;
	head_imgs[FINISH_PERS]->w    = Get_image(FINISH_NORMAL_IMG)->w;
	head_imgs[FINISH_PERS]->h    = Get_image(FINISH_NORMAL_IMG)->h;
	head_imgs[FINISH_PERS]->type = NORM_TYPE;

	/* Setting head_blocks values */

	for (i = 0; i < levels->lvls[level_number]->blocks_count; ++i)
		Add_head_block(levels->lvls[level_number]->x[i], 
					   levels->lvls[level_number]->y[i], 
			           levels->lvls[level_number]->w[i], 
			           levels->lvls[level_number]->h[i], 
			           levels->lvls[level_number]->types[i]);
	return 0;
}

int Add_head_block(int x, int y, int w, int h, int type){
	Coord_t* new_block = (Coord_t*)calloc(sizeof(Coord_t), 1);
	if (new_block == NULL) return -1;

	new_block->x = x;
	new_block->y = y;
	new_block->w = w;
	new_block->h = h;
	new_block->vx = 0;
	new_block->vy = 0;
	new_block->time = 3;
	new_block->type = type;
	new_block->next = NULL;

	if (NULL == head_blocks){
		head_blocks = new_block;
		head_blocks->next = NULL;
	}
	else{
		new_block->next = head_blocks;
		head_blocks = new_block;
	}

	return 0;
}

int Del_head_block(Coord_t* block){
	Coord_t* cur_block = head_blocks;

	if (head_blocks == block){
		head_blocks = block->next;
		free(block);
	}
	else{
		while (NULL != cur_block && NULL != cur_block->next && cur_block->next != block)
			cur_block = cur_block->next;

		if (cur_block->next == block){
			cur_block->next = block->next;
			free(block);
		}
	}

	return 0;
}

Coord_t* Get_head_img(size_t index){
	if (index < PERS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

int Max_hor_step(Coord_t* one, int stepX, Coord_t* two){
	/* 	return max step which first object can do on the horizontal axis */

	/* If objects be on different height */
	if (one->y > two->y + two->h - 1) return stepX; 
	if (one->y + one->h - 1 < two->y) return stepX;
	/*  */

	if (stepX > 0)
		if (one->x + stepX < two->x && one->x + one->w - 1 + stepX > two->x) 
			return two->x - (one->x + one->w - 1);
	if (stepX < 0)
		if (one->x + stepX < two->x + two->w && one->x + one->w - 1 + stepX > two->x + two->w) 
			return one->x - (two->x + two->w);

	return stepX;
}

int Max_ver_step(Coord_t* one, int stepY, Coord_t* two){
	/* 	return max step which first object can do on the vertical axis */

	/* If objects be on different width */
	if (one->x > two->x + two->w - 1) return stepY; 
	if (one->x + one->w - 1 < two->x) return stepY;
	/*  */

	if (stepY > 0)
		if (one->y + stepY < two->y + two->h - 1 && one->y + one->h - 1 + stepY > two->y + two->h -1) 
			return one->y - (two->y + two->h - 1);
	if (stepY < 0)
		if (one->y < two->y && one->y + one->h - 1 + stepY > two->y) 
			return two->y - (one->y + one->h);

	return stepY;
}

void Move_heroes_on_ox(int step){
	int max_way = step;
	Coord_t* cur_block = head_blocks;

	while (NULL != cur_block->next && NULL != cur_block){
		max_way = min(abs(Max_hor_step(head_imgs[HEROES_PERS], step, cur_block)), abs(max_way));

		if (NULL != cur_block->next)
			cur_block = cur_block ->next;
	}

	if (step < 0) head_imgs[HEROES_PERS]->x -= max_way;
	else 		  head_imgs[HEROES_PERS]->x += max_way;
}
/*
void Detection_gold_blocks(void){
	Coord_t* cur = head_blocks;

	while (NULL != cur){*/
		/* detection blocks which top */
		/*if (one->y > two->y + two->h - 1 || one->y + one->h - 1 < two->y) return stepX;
		if (cur->)
*/

		/* To next block */
		/*cur = cur ->next;
	}
}

void Сollision_detection(void){
	Detection_gold_blocks(); 
}*/

void Restart_level(int l){

}

void CleanUp_heads(void){
	
}

void Update_screen(void){
	Coord_t* cur = NULL;
	/* Drawing background */
	Draw_background();
	/* Drawing heroes */
	if (head_imgs[HEROES_PERS]->type == NORM_TYPE) 
		Draw_heroes(HEROES_NORMAL_IMG, 
			        head_imgs[HEROES_PERS]->x, 
			        head_imgs[HEROES_PERS]->y);
	else if (head_imgs[HEROES_PERS]->type == GOLD_TYPE) 
		Draw_heroes(HEROES_GOLD_IMG, 
			        head_imgs[HEROES_PERS]->x, 
			        head_imgs[HEROES_PERS]->y);

	/* Drawing finish */
	if (head_imgs[FINISH_PERS]->type == NORM_TYPE) 
		Draw_finish(FINISH_NORMAL_IMG, 
			        head_imgs[FINISH_PERS]->x, 
			        head_imgs[FINISH_PERS]->y);
	else if (head_imgs[FINISH_PERS]->type == GOLD_TYPE) 
		Draw_finish(FINISH_GOLD_IMG, 
			        head_imgs[FINISH_PERS]->x, 
			        head_imgs[FINISH_PERS]->y);

	/* Drawing blocks */
	cur = head_blocks;
	while(cur != NULL){
		if      (cur->type == NORM_TYPE) 
			Draw_block(GRAY_BLOCK, cur->x, cur->y, cur->w, cur->h);
		else if (cur->type == GOLD_TYPE) 
			Draw_block(GOLD_BLOCK, cur->x, cur->y, cur->w, cur->h);
		else if (cur->type == BLUE_TYPE) 
			Draw_block(BLUE_BLOCK, cur->x, cur->y, cur->w, cur->h);

		cur = cur->next;
	}
}