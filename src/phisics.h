#ifndef _PHISICS_H_
	#define _PHISICS_H_

	#define max(a, b) (a > b ? a : b)
	#define min(a, b) (a < b ? a : b)
	#define GRAVIT_CONST 0.05

	enum{
		HEROES_PERS,
		FINISH_PERS,
		PERS_TOTAL
	};

	typedef struct Coord_t{
		struct Coord_t* next;

		float vx;
		float vy;
		float time;

		short type;
		short x;
		short y;
		short w;
		short h;
	} Coord_t;

void Set_heads_imgs(void);
Coord_t* Get_head_img(size_t index);

void Move_heroes_on_ox(int step);
int Init_phisics(char* levelsFileName);

int Add_head_block(int x, int y, int w, int h, int type);
int Del_head_block(Coord_t* block);
void Update_screen(void);

void CleanUp_heads(void);

#endif