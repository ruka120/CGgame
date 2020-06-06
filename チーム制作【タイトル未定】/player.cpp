#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "stage.h"
#include "player.h"

using namespace GameLib;
using namespace input;
enum MOVE_VECTOR//�ړ�����
{
	Stop=0,
	Right,
	Left,
	Up,
	Down,
};
//�ړ��t���O
//int XorY -> �������ɓ������������ɓ�����(x->0,y->1)
//float distance -> �ړ�����
//int time -> ���t���[�������Ĉړ����邩
void PLAYER::move(float distance,int time)
{
	static int count = 0;
	switch (move_vector)
	{
	default://�ړ������ȊO�������Ă�����I��
		return;
	case MOVE_VECTOR::Left:
		pos.x -= (distance / time);
		count++;
		break;
	case MOVE_VECTOR::Right:
		pos.x += (distance / time);
		count++;
		break;
	case MOVE_VECTOR::Up:
		pos.y -= (distance / time);
		count++;
		break;
	case MOVE_VECTOR::Down:
		pos.y += (distance / time);
		count++;
		break;
	}
	if (count == time)
	{
		move_vector = MOVE_VECTOR::Stop;
		chip_num = get_nowCnum(center);
		count = 0;
	}
}
namespace STATG
{
 VECTOR2 end;
 VECTOR2 start;
}
#if _DEBUG
void PLAYER::reset()
{
	pos = Pstart();
	life = 16;
	center = { pos.x + 32,pos.y + 32 };
	chip_num = get_nowCnum(center);
	move_vector = MOVE_VECTOR::Stop;
}
#endif
void PLAYER::init()
{
	pos = Pstart();
	STATG::start = Sstart();
	STATG::end = Send();
	life = 16;
	distance = get_Csize();
	center = { pos.x + 32,pos.y + 32 };
	chip_num = get_nowCnum(center);
	move_vector = MOVE_VECTOR::Stop;
	
}

void PLAYER::update()
{
	center = { pos.x + 32,pos.y + 32 };
	
	//�ړ�
	if(life && !move_vector)
	{ 
		if ( TRG(0)&PAD_RIGHT&&get_Ctype(chip_num.x+1, chip_num.y)!=STAGE_TYPE::Wall ) { life--; move_vector = MOVE_VECTOR::Right; }
		if ( TRG(0)&PAD_LEFT &&get_Ctype(chip_num.x-1, chip_num.y)!=STAGE_TYPE::Wall ) { life--; move_vector = MOVE_VECTOR::Left;  }
		if ( TRG(0)&PAD_UP   &&get_Ctype(chip_num.x, chip_num.y-1)!=STAGE_TYPE::Wall ) { life--; move_vector = MOVE_VECTOR::Up;    }
		if ( TRG(0)&PAD_DOWN &&get_Ctype(chip_num.x, chip_num.y+1)!=STAGE_TYPE::Wall ) { life--; move_vector = MOVE_VECTOR::Down;  }
	 
	}
	debug::setString("life::%d", life);
	debug::setString("X::%d Y::%d", chip_num.x, chip_num.y);
	if (move_vector) 
	{
		switch (move_vector)
		{
		case MOVE_VECTOR::Left:
		case MOVE_VECTOR::Right:
			move(distance.x, 60);
			break;
		case MOVE_VECTOR::Up:
		case MOVE_VECTOR::Down:
			move(distance.y, 60);
			break;
		}
	}
#if _DEBUG
	//�ړ��񐔂̃��Z�b�g
	if (TRG(0)&PAD_F1) { reset(); }
#endif
	//�ړ�����
	if (pos.x < STATG::start.x) pos.x = STATG::start.x;
	if (pos.x > STATG::end.x)   pos.x = STATG::end.x;
	if (pos.y < STATG::start.y) pos.y = STATG::start.y;
	if (pos.y > STATG::end.y)   pos.y = STATG::end.y;
	if (!life)debug::setString("GAME OBER");
}

void PLAYER::draw()
{
	debug::display();
	primitive::rect(pos.x, pos.y,64,64,0,0,0,1,1,1,0.8);
}

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
PLAYER player;
void player_init()
{
	player.init();
}

void player_update()
{
	player.update();
}

void player_draw()
{
	player.draw();
}
