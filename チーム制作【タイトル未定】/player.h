#pragma once
#include "add_on.h"
class PLAYER :public OBJ
{
public:
	int move_flg;//�ړ��t���O
	int life;//�s����
	//�ړ��t���O
	//int XorY -> �������ɓ������������ɓ�����(x->0,y->1)
	//float distance -> �ړ�����
	//int time -> ���t���[�������Ĉړ����邩
	void move(float distance, int time);
};
void player_init();
void player_update();
void player_draw();
