#pragma once
#include "add_on.h"
enum PLAYER_STATE
{
	GAME_OVER = -1,//GAME OVER
	Think = 0,     //�v�l
	Move,          //�ړ�
	Bounce,        //���˕Ԃ�
	Destroy,       //�u���b�N�j��
};
class PLAYER :public OBJ
{
private:
	CHIP_NUM chip_num;//���݂̃}�b�v�`�b�v��̔ԍ�
	int move_vector;  //�ړ�����
	int life;         //�s����
	VECTOR2 distance; //�ړ�����
	VECTOR2 center;   //���S���W
	void reset();     //���Z�b�g�֐�
	void think();     //�v�l�֐�
	void move();      //�ړ��֐�
	void bounce();    //���˕Ԃ�֐�
	
#if (_DEBUG)
	void STATUS();
#endif
public:
	void init();
	void update();
	void draw();
};
void player_init();
void player_update();
void player_draw();
