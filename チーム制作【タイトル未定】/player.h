#pragma once
#include "add_on.h"
class PLAYER :public OBJ
{
public:
	int move_vector;//移動方向
	int life;//行動回数
	
	void move(float distance, int time);
};
void player_init();
void player_update();
void player_draw();
