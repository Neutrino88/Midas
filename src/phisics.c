#include "stdio.h"
#include "malloc.h"

#include "phisics.h"
#include "draw_game.h"
#include "levels.h"

Coord_t* head_imgs[PERS_TOTAL];
Coord_t* head_blocks;

short heroes_pos;
short finish_pos;

Levels_t* levels;
int	level_number;

int Init_phisics(char* levelsFileName){
	Create_levels("levels");
	/* Reading levels */
	levels = Read_levels(levelsFileName);
	if (levels == NULL) return !0;

	/* Setting head_img values of clouds */
	head_imgs[CLOUD_1_PERS] = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[CLOUD_1_PERS]->next = NULL;
	head_imgs[CLOUD_1_PERS]->vx   = 1;
	head_imgs[CLOUD_1_PERS]->vy   = 0;
	head_imgs[CLOUD_1_PERS]->x    = 120;
	head_imgs[CLOUD_1_PERS]->y    = 40;
	head_imgs[CLOUD_1_PERS]->w    = Get_image(CLOUD_1_IMG)->w;
	head_imgs[CLOUD_1_PERS]->h    = Get_image(CLOUD_1_IMG)->h;

	head_imgs[CLOUD_2_PERS] = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[CLOUD_2_PERS]->next = NULL;
	head_imgs[CLOUD_2_PERS]->vx   = 1;
	head_imgs[CLOUD_2_PERS]->vy   = 0;
	head_imgs[CLOUD_2_PERS]->x    = 0;
	head_imgs[CLOUD_2_PERS]->y    = 5;
	head_imgs[CLOUD_2_PERS]->w    = Get_image(CLOUD_2_IMG)->w;
	head_imgs[CLOUD_2_PERS]->h    = Get_image(CLOUD_2_IMG)->h;

	head_imgs[CLOUD_3_PERS] = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[CLOUD_3_PERS]->next = NULL;
	head_imgs[CLOUD_3_PERS]->vx   = 1;
	head_imgs[CLOUD_3_PERS]->vy   = 0;
	head_imgs[CLOUD_3_PERS]->x    = 5;
	head_imgs[CLOUD_3_PERS]->y    = 120;
	head_imgs[CLOUD_3_PERS]->w    = Get_image(CLOUD_3_IMG)->w;
	head_imgs[CLOUD_3_PERS]->h    = Get_image(CLOUD_3_IMG)->h;

	level_number = 0;
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
void Del_head_block(Coord_t* block){
	Coord_t* cur_block = head_blocks;

	if (NULL == block){
		return;
	}
	else if (head_blocks == block){
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
}
Coord_t* Get_head_img(size_t index){
	if (index < PERS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

int Max_hor_step(Coord_t* one, int stepX, Coord_t* two){
	/* 	return max step (<= stepX) which first object can do on the horizontal axis */

	/* If objects be on different height */
	if (!On_one_hor_line(one, two)) return stepX; 

	if (stepX > 0 &&
		one->x + stepX < two->x && 
		one->x + one->w - 1 + stepX > two->x) 
			return two->x - (one->x + one->w - 1);
	if (stepX < 0 &&
		one->x + stepX < two->x + two->w && 
		one->x + one->w - 1 + stepX > two->x + two->w) 
			return one->x - (two->x + two->w);
	
	return stepX;
}
int Max_ver_step(Coord_t* one, int stepY, Coord_t* two){
	/* 	return max step (<= stepY) which first object can do on the vertical axis */

	/* If objects be on different width */
	if (!On_one_ver_line(one, two)) return stepY; 

	if (stepY < 0 &&
		one->y + stepY < two->y + two->h && 
		one->y + one->h - 1 + stepY > two->y + two->h)
			return one->y - (two->y + two->h);

	if (one != head_imgs[HEROES_PERS] &&
		one != head_imgs[FINISH_PERS] &&
		stepY > 0 &&
		one->y < two->y && 
		one->y + one->h + stepY >= two->y)
			return two->y - (one->y + one->h);

	if (stepY > 0 &&
		one->y < two->y && 
		one->y + one->h - 1 + stepY >= two->y)
			return two->y - (one->y + one->h - 1);
	
	return stepY;
}
int On_one_hor_line(Coord_t* one, Coord_t* two){
	/* 
	return !0:
		if first object have vertical projection on second object
	return 0:
		else
 	*/
	if (two->y >= one->y && 
		two->y <  one->y + one->h - 1) return !0;
	if (one->y >= two->y && 
		one->y <  two->y + two->h - 1) return !0;

	return 0;
}
int On_one_ver_line(Coord_t* one, Coord_t* two){
	/* 	return !0:
		if first object have horizontal projection on second object
	return 0:
		else
 */
	if (two->x >= one->x && 
		two->x <  one->x + one->w - 1) return !0;
	if (one->x >= two->x && 
		one->x <  two->x + two->w - 1) return !0;
	return 0;
}
int Move_object_on_oy(Coord_t* object, int step){
	int max_way = step;
	Coord_t* cur_block = head_blocks;

	/* Detection collision object and blocks */
	while (NULL != cur_block){
		if (object != cur_block)
			max_way = min(abs(Max_ver_step(object, step, cur_block)), abs(max_way));

		cur_block = cur_block->next;
	}
	/* Detection collision object and heroes  */
	if (object != head_imgs[HEROES_PERS])
		max_way = min(abs(Max_ver_step(object, step, head_imgs[HEROES_PERS])), abs(max_way));	
	/* Detection collision object and finish  */
	if (object != head_imgs[FINISH_PERS])
		max_way = min(abs(Max_ver_step(object, step, head_imgs[FINISH_PERS])), abs(max_way));

	if (step < 0) object->y -= max_way;
	else 		  object->y += max_way;

	return max_way;
}
void Move_heroes_on_ox(int step){
	int max_way = step;
	Coord_t* cur_block = head_blocks;

	/* Detection collision heroes and blocks */
	while (NULL != cur_block){
		max_way = min(abs(Max_hor_step(head_imgs[HEROES_PERS], step, cur_block)), abs(max_way));

		cur_block = cur_block ->next;
	}
	/* Detection collision heroes and finish  */
	max_way = min(abs(Max_hor_step(head_imgs[HEROES_PERS], step, head_imgs[FINISH_PERS])), abs(max_way));

	if (step < 0) head_imgs[HEROES_PERS]->x -= max_way;
	else 		  head_imgs[HEROES_PERS]->x += max_way;
}

void Jump_heroes_on_oy(void){
	if (heroes_pos == ON_THE_BLOCK_POS)
		head_imgs[HEROES_PERS]->vy = -12 * GRAVIT_CONST;
}

int Detection_victory_of_the_heroes(void){
	Coord_t* fin = head_imgs[FINISH_PERS];	/* finish */
	Coord_t* her = head_imgs[HEROES_PERS];	/* heroes */

	/* if heroes is normal or finish is gold then return*/
	if (NORM_TYPE != her->type) return 0;
	if (NORM_TYPE != fin->type) return 0;

	/* detection of blocks which top */
	if ( (On_one_ver_line(her, fin) && her->y == fin->y + fin->h) ||
	/* detection of blocks which botton */
	     (On_one_ver_line(her, fin) && her->y + her->h - 1 == fin->y) ||
	/* detection of blocks which to the left */
	     (On_one_hor_line(her, fin) && her->x == fin->x + fin->w) ||
	/* detection of blocks which to the right */
	     (On_one_hor_line(her, fin) && her->x + her->w - 1 == fin->x) )
	 	 return !0;

	return 0;
}
void Detection_gold_blocks(void){
	Coord_t* cur = head_blocks;				/* current block */
	Coord_t* her = head_imgs[HEROES_PERS];	/* heroes */
	Uint32 curTime = SDL_GetTicks();

	/* if heroes isn't gold */
	if (GOLD_TYPE != her->type) return;

	while (NULL != cur){
		/* if heroes shouln't make gold */ 
		if (NORM_TYPE != cur->type) {
			cur = cur->next;
			continue;
		}

		/* detection of blocks which top */
		if ( (On_one_ver_line(her, cur) && her->y == cur->y + cur->h + 1) ||
		/* detection of blocks which botton */
		     (On_one_ver_line(her, cur) && her->y + her->h - 1 == cur->y) ||
		/* detection of blocks which to the left */
		     (On_one_hor_line(her, cur) && her->x == cur->x + cur->w) ||
		/* detection of blocks which to the right */
		     (On_one_hor_line(her, cur) && her->x + her->w - 1 == cur->x) ){
		     
			 cur->time = curTime;
		     cur->type = GOLD_TYPE;
		}

		/* To next block */
		cur = cur->next;
	}
}
void Detection_heroes_to_normal_type(void){
	Coord_t* cur = head_blocks;				/* current block */
	Coord_t* her = head_imgs[HEROES_PERS];	/* heroes */

	/* if heroes is normal */
	if (NORM_TYPE == her->type) return;

	while (NULL != cur){
		/* if current block isn't blue */ 
		if (BLUE_TYPE != cur->type) {
			cur = cur->next;
			continue;
		}

		/* detection of blocks which top */
		if ( (On_one_ver_line(her, cur) && her->y == cur->y + cur->h + 1) ||
		/* detection of blocks which botton */
		     (On_one_ver_line(her, cur) && her->y + her->h - 1 == cur->y) ||
		/* detection of blocks which to the left */
		     (On_one_hor_line(her, cur) && her->x == cur->x + cur->w) ||
		/* detection of blocks which to the right */
		     (On_one_hor_line(her, cur) && her->x + her->w - 1 == cur->x) )
		     her->type = NORM_TYPE;

		/* To next block */
		cur = cur->next;
	}
}
void Detection_finish_to_gold_type(void){
	Coord_t* fin = head_imgs[FINISH_PERS];	/* current block */
	Coord_t* her = head_imgs[HEROES_PERS];	/* heroes */

	/* if heroes is normal or finish is gold then return*/
	if (NORM_TYPE == her->type) return;
	if (GOLD_TYPE == fin->type) return;

	/* detection of blocks which top */
	if ( (On_one_ver_line(her, fin) && her->y == fin->y + fin->h) ||
	/* detection of blocks which botton */
	     (On_one_ver_line(her, fin) && her->y + her->h - 1 == fin->y) ||
	/* detection of blocks which to the left */
	     (On_one_hor_line(her, fin) && her->x == fin->x + fin->w) ||
	/* detection of blocks which to the right */
	     (On_one_hor_line(her, fin) && her->x + her->w - 1 == fin->x) )
	     fin->type = GOLD_TYPE;
}
void Collision_detection(void){
	Detection_gold_blocks();
	Detection_heroes_to_normal_type();
	Detection_finish_to_gold_type();
	Detection_victory_of_the_heroes();
}

int Restart_level(int lvl_number){
	int i;
	Uint32 curTime;
	/* Cleaning heads*/
	CleanUp_heads();

	/* Setting level number */
	if 		(-3 == lvl_number && level_number > 0) 
		--level_number;	
	else if (-2 == lvl_number && level_number < levels->lvls_count) 
		++level_number;
	else if (-1 != lvl_number) 
		level_number = lvl_number;

	level_number = abs(level_number % levels->lvls_count);

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

	head_imgs[FINISH_PERS] = (Coord_t*)malloc(sizeof(Coord_t));
	head_imgs[FINISH_PERS]->next = NULL;
	head_imgs[FINISH_PERS]->vx   = 0;
	head_imgs[FINISH_PERS]->vy   = 0;
	head_imgs[FINISH_PERS]->x    = levels->lvls[level_number]->finish.x;
	head_imgs[FINISH_PERS]->y    = levels->lvls[level_number]->finish.y;;
	head_imgs[FINISH_PERS]->w    = Get_image(FINISH_NORMAL_IMG)->w;
	head_imgs[FINISH_PERS]->h    = Get_image(FINISH_NORMAL_IMG)->h;
	head_imgs[FINISH_PERS]->type = NORM_TYPE;

	/* Setting head_blocks values */
	curTime = SDL_GetTicks();
	for (i = 0; i < levels->lvls[level_number]->blocks_count; ++i){
		Add_head_block(levels->lvls[level_number]->x[i], 
					   levels->lvls[level_number]->y[i], 
			           levels->lvls[level_number]->w[i], 
			           levels->lvls[level_number]->h[i], 
			           levels->lvls[level_number]->types[i]);

		if (head_blocks->type == GOLD_TYPE)
			head_blocks->time = curTime;
	}

	/* Checking heroes and finish pos */
	Checking_heroes_and_finish_pos();
	return 0;
}

void Checking_heroes_and_finish_pos(void){
	Coord_t* cur = head_blocks;
	int max_way_heroes = 1;
	int max_way_finish = 1;

	while (NULL != cur){
		if (max_way_heroes == 1)
			max_way_heroes = min(abs(Max_ver_step(head_imgs[HEROES_PERS], 1, cur)), abs(max_way_heroes));
		if (max_way_finish == 1)
			max_way_finish = min(abs(Max_ver_step(head_imgs[FINISH_PERS], 1, cur)), abs(max_way_finish));

		cur = cur->next;
	}

	max_way_heroes = min(abs(Max_ver_step(head_imgs[HEROES_PERS], 1, head_imgs[FINISH_PERS])), abs(max_way_heroes));
	max_way_finish = min(abs(Max_ver_step(head_imgs[FINISH_PERS], 1, head_imgs[HEROES_PERS])), abs(max_way_finish));	

	heroes_pos = (0 == max_way_heroes) ? ON_THE_BLOCK_POS : IN_THE_AIR_POS;
	finish_pos = (0 == max_way_finish) ? ON_THE_BLOCK_POS : IN_THE_AIR_POS;
}

void CleanUp_heads(void){
	/* CleanUp head_imgs */
	if (NULL != head_imgs[HEROES_PERS]) free(head_imgs[HEROES_PERS]);
	if (NULL != head_imgs[FINISH_PERS]) free(head_imgs[FINISH_PERS]);

	/* CleanUp head_blocks variable */
	while (NULL != head_blocks){
		Del_head_block(head_blocks);
	}
}

void Update_screen(void){
	Coord_t* cur = NULL;
	/* Drawing background */
	Draw_background();
	/* Drawing clouds */
	Draw_cloud(CLOUD_1_IMG,
		head_imgs[CLOUD_1_PERS]->x,
		head_imgs[CLOUD_1_PERS]->y);
	Draw_cloud(CLOUD_2_IMG,
		head_imgs[CLOUD_2_PERS]->x,
		head_imgs[CLOUD_2_PERS]->y);
	Draw_cloud(CLOUD_3_IMG,
		head_imgs[CLOUD_3_PERS]->x,
		head_imgs[CLOUD_3_PERS]->y);

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

void MoveClouds(int moveCl_1, int moveCl_2, int moveCl_3){
	/* Moving clouds */
	if (moveCl_1){
		if (head_imgs[CLOUD_1_PERS]->x < 801) 
			head_imgs[CLOUD_1_PERS]->x = head_imgs[CLOUD_1_PERS]->x + head_imgs[CLOUD_1_PERS]->vx;
		else 
			head_imgs[CLOUD_1_PERS]->x = -200;
	}

	if (moveCl_2){
		if (head_imgs[CLOUD_2_PERS]->x < 801) 
			head_imgs[CLOUD_2_PERS]->x = head_imgs[CLOUD_2_PERS]->x + head_imgs[CLOUD_2_PERS]->vx;
		else 
			head_imgs[CLOUD_2_PERS]->x = -200;
	}
	
	if (moveCl_3){
		if (head_imgs[CLOUD_3_PERS]->x < 801) 
			head_imgs[CLOUD_3_PERS]->x = head_imgs[CLOUD_3_PERS]->x + head_imgs[CLOUD_3_PERS]->vx;
		else 
			head_imgs[CLOUD_3_PERS]->x = -200;
	}
}

void Phisics_update(void){
	Coord_t* her = head_imgs[HEROES_PERS]; 
	Coord_t* fin = head_imgs[FINISH_PERS];
	Coord_t* cur = head_blocks;
	Uint32 curTime;

	/* Moving blocks */
	curTime = SDL_GetTicks();
	while (NULL != cur){
		/* If levitation time of current block is over then increment speed*/
		if (cur->type == GOLD_TYPE && curTime - cur->time >= LEVITATION_TIME)
			cur->vy += GRAVIT_CONST;

		/* If speed of current block <> 0 */
		if (cur->vy != 0 &&
			0 == Move_object_on_oy(cur, cur->vy))
			cur->vy = 0;
		/*
		printf("%i %f\n", cur->y, cur->vy);*/

		/* If current block dropped then delete this blos*/
		if (cur->y > 1000){
			Coord_t* next_block = cur->next;
			Del_head_block(cur);
			cur = next_block;
		}
		else
			cur = cur->next;
	}

	/* Moving heroes */
	Checking_heroes_and_finish_pos();

	if (heroes_pos == IN_THE_AIR_POS)	
		her->vy += GRAVIT_CONST;
	else if (heroes_pos == ON_THE_BLOCK_POS && her->vy > 0)
		her->vy = 0;

	if (her->vy != 0 && her->y < 1000)
		Move_object_on_oy(her, her->vy);

	/* Moving finish */
	if (finish_pos == IN_THE_AIR_POS)	
		fin->vy += GRAVIT_CONST;
	else if (finish_pos == ON_THE_BLOCK_POS && fin->vy > 0)
		fin->vy = 0;

	if (fin->vy != 0 && fin->y < 1000)
		Move_object_on_oy(fin, fin->vy);

	/* if was moving */
	if (her->vy != 0 || fin->vy != 0)
		Collision_detection();
}	

int Check_game_over(void){
	if (GOLD_TYPE == Get_head_img(FINISH_PERS)->type ||
		head_imgs[HEROES_PERS]->y > 1000){ 
			Draw_you_lost(320, 180);
			return 1;
	}

	if (Detection_victory_of_the_heroes()) {
			Draw_you_won(270, 180);
			return 2;
	}

	return 0;
}