#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "player.h"

#include "stage.h"

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
		count = 0;
	}
}
PLAYER player;


namespace STATG
{
 VECTOR2 end;
 VECTOR2 start;
}
#if _DEBUG
void reset()
{
	player.pos = { Pstart(0).x,Pstart(0).y };
	player.life = 16;
	player.move_vector = MOVE_VECTOR::Stop;
}
#endif
void player_init()
{
	player.pos = { Pstart(0).x,Pstart(0).y };
	STATG::start = Sstart(0);
	STATG::end = Send(0);
	player.life = 16;
	player.move_vector = MOVE_VECTOR::Stop;
}

void player_update()
{
	
	//�ړ�
	if(player.life && !player.move_vector)
	{ 
		if ( TRG(0)&PAD_RIGHT ) { player.life--; player.move_vector = MOVE_VECTOR::Right; }
		if ( TRG(0)&PAD_LEFT  ) { player.life--; player.move_vector = MOVE_VECTOR::Left;  }
		if ( TRG(0)&PAD_UP    ) { player.life--; player.move_vector = MOVE_VECTOR::Up;    }
		if ( TRG(0)&PAD_DOWN  ) { player.life--; player.move_vector = MOVE_VECTOR::Down;  }
	 
	}
	debug::setString("life::%d", player.life);
	if (player.move_vector) { player.move(64, 60); }
#if _DEBUG
	//�ړ��񐔂̃��Z�b�g
	if (TRG(0)&PAD_F1) { reset(); }
#endif
	//�ړ�����
	if (player.pos.x < STATG::start.x) player.pos.x = STATG::start.x;
	if (player.pos.x > STATG::end.x)   player.pos.x = STATG::end.x;
	if (player.pos.y < STATG::start.y) player.pos.y = STATG::start.y;
	if (player.pos.y > STATG::end.y)   player.pos.y = STATG::end.y;
	if (!player.life)debug::setString("GAME OBER");
}

void player_draw()
{
	debug::display();
	primitive::rect(player.pos.x, player.pos.y,64,64,0,0,0,1,1,1,0.8);
}

