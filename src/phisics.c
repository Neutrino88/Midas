#include "stdio.h"
#include "images.h"
#include "phisics.h"
#include "malloc.h"

Coord* head_imgs[PERS_TOTAL];
Coord* head_blocks[PERS_TOTAL];

Coord* Get_head_img(size_t index){
	if (index < PERS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

void Set_head_img(size_t index){
	if (index >= PERS_TOTAL) return;

	head_imgs[index] = (Coord*)malloc(sizeof(Coord));
	head_imgs[index]->w = Get_image(index)->w;
	head_imgs[index]->h = Get_image(index)->h;
	head_imgs[index]->x = 0;
	head_imgs[index]->y = 0;
	head_imgs[index]->vx = 0;
	head_imgs[index]->vy = 0;

	printf("Set_heads_img %i\n", (int)index);
	printf("%u (%u, %u)\n", (int)index, (int)head_imgs[index]->w, (int)head_imgs[index]->h);
}

void Set_heads_imgs(void){
	size_t i;
	
	for (i = 0; i < PERS_TOTAL; ++i)
		Set_head_img(i);
}

void Move_heroes_on_Ox(int step){
	
}