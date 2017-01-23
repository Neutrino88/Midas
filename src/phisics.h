#ifndef _PHISICS_H_
	#define _PHISICS_H_

	#define max(a, b) (a > b ? a : b)
	#define min(a, b) (a < b ? a : b)
	#define GRAVIT_CONST 1
	#define LEVITATION_TIME 1500

	enum{
		HEROES_PERS,
		FINISH_PERS,
		CLOUD_1_PERS,
		CLOUD_2_PERS,
		CLOUD_3_PERS,
		PERS_TOTAL
	};

	enum{
		ON_THE_BLOCK_POS,
		IN_THE_AIR_POS,
		POS_TOTAL
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

void Jump_heroes_on_oy(void);
void Move_heroes_on_ox(int step);
int Move_object_on_oy(Coord_t* object, int step);
void MoveClouds(int moveCl_1, int moveCl_2, int moveCl_3);
int Init_phisics(char* levelsFileName);

int On_one_hor_line(Coord_t* one, Coord_t* two);
int On_one_ver_line(Coord_t* one, Coord_t* two);

void Detection_finish_to_gold_type(void);
void Detection_heroes_to_normal_type(void);
void Detection_gold_blocks(void);
void Collision_detection(void);

void Checking_heroes_and_finish_pos(void);

int Add_head_block(int x, int y, int w, int h, int type);
void Del_head_block(Coord_t* block);
void Update_screen(void);
void Phisics_update(void);

void CleanUp_heads(void);

int Restart_level(int level_number);
int Game_over(void);
#endif