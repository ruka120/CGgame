#pragma once
#include "add_on.h"
class PLAYER :public OBJ
{
public:
	int move_vector;//�ړ�����
	int life;//�s����
	
	void move(float distance, int time);
};
void player_init();
void player_update();
void player_draw();
