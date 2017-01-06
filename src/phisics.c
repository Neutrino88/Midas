#include "stdio.h"
#include "load_img.h"
#include "phisics.h"

Coord* head_imgs[IMGS_TOTAL];

Coord* Get_head_img(size_t index){
	if (index < IMGS_TOTAL) return head_imgs[index];
	else 					return NULL;
}

