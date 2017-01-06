#ifndef _DRAW_H_
#define _DRAW_H_

int  Draw_img (size_t x, size_t y, SDL_Surface* src_surface);
void Fill_rect(size_t x, size_t y, size_t w, size_t h, size_t red, size_t green, size_t blue);

#endif