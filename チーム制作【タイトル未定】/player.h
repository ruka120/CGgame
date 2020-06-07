#pragma once
#include "add_on.h"

class PLAYER :public OBJ
{
private:
	CHIP_NUM chip_num;//���݂̃}�b�v�`�b�v��̔ԍ�
	int move_vector;//�ړ�����
	int life;//�s����
	VECTOR2 center;  //���S���W
	void move(int time);
	void reset();
#if (_DEBUG)
	void PLAYER::STATUS();
#endif
public:
	void init();
	void update();
	void draw();
};
void player_init();
void player_update();
void player_draw();
