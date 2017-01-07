#include "stdio.h"
#include "malloc.h"

#include "game.h"

Coord* head_imgs[PERS_TOTAL];

Coord* head_blocks;
size_t blocks_total  = 0;

size_t current_level = 0;

Coord* Get_head_img(size_t index){
	if (index < PERS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

void Set_head_img(size_t index){
	if (index >= PERS_TOTAL) return;

	head_imgs[index] = (Coord*)malloc(sizeof(Coord));
	/*head_imgs[index]->w = Get_image(index)->w;
	head_imgs[index]->h = Get_image(index)->h;*/
	head_imgs[index]->x = 0;
	head_imgs[index]->y = 0;
	head_imgs[index]->vx = 0;
	head_imgs[index]->vy = 0;
}

void Set_heads_imgs(void){
	size_t i;
	
	for (i = 0; i < PERS_TOTAL; ++i)
		Set_head_img(i);
}

void Set_head_blocks(){

}

void Move_heroes_on_Ox(int step){

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