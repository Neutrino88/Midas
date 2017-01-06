#include "stdio.h"
#include "load_img.h"
#include "phisics.h"
#include "load_img.h"
#include "malloc.h"

Coord* head_imgs[IMGS_TOTAL];

Coord* Get_head_img(size_t index){
	if (index < IMGS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

void Set_head_img(size_t index){
	if (index >= IMGS_TOTAL) return;

	head_imgs[index] = (Coord*)malloc(sizeof(Coord));
	head_imgs[index]->w = Get_image(index)->w;
	head_imgs[index]->h = Get_image(index)->h;
	printf("Set_heads_img %i\n", (int)index);
	printf("%u (%u, %u)\n", (int)index, (int)head_imgs[index]->w, (int)head_imgs[index]->h);
}

void Set_heads_imgs(void){
	size_t i;
	
	for (i = 0; i < IMGS_TOTAL; ++i)
		Set_head_img(i);
}