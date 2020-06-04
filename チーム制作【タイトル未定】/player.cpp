#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "player.h"

#include "stage.h"

using namespace GameLib;
using namespace input;
enum MOVE_VECTOR//プレイヤーの移動方向
{
	Stop=0,
	Right,
	Left,
	Up,
	Down,
};

void PLAYER::move(float distance,int time)
{
	static int count = 0;
	switch (move_flg)
	{
	default://0,1以外が入っていたら終了
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
		move_flg = MOVE_VECTOR::Stop;
		count = 0;
	}
}
PLAYER player;


namespace STATG
{
 VECTOR2 end;
 VECTOR2 start;
}
void reset()
{
	player.pos = { Pstart(0).x,Pstart(0).y };
	player.life = 16;
	player.move_flg = MOVE_VECTOR::Stop;
}
void player_init()
{
	player.pos = { Pstart(0).x,Pstart(0).y };
	STATG::start = Sstart(0);
	STATG::end = Send(0);
	player.life = 16;
	player.move_flg = MOVE_VECTOR::Stop;
}

void player_update()
{
	
	//移動
	if(player.life)
	{ 
		if (TRG(0)&PAD_RIGHT && !player.move_flg) { player.life--; player.move_flg = MOVE_VECTOR::Right; }
		if (TRG(0)&PAD_LEFT  && !player.move_flg) { player.life--; player.move_flg = MOVE_VECTOR::Left;  }
		if (TRG(0)&PAD_UP    && !player.move_flg) { player.life--; player.move_flg = MOVE_VECTOR::Up;    }
		if (TRG(0)&PAD_DOWN  && !player.move_flg) { player.life--; player.move_flg = MOVE_VECTOR::Down;  }
	 
	}
	if (player.move_flg) { player.move(64, 10); }
	//移動回数のリセット
	if (TRG(0)&PAD_F1) { reset(); }
	//移動制限
	if (player.pos.x < STATG::start.x) player.pos.x = STATG::start.x;
	if (player.pos.x > STATG::end.x)   player.pos.x = STATG::end.x;
	if (player.pos.y < STATG::start.y) player.pos.y = STATG::start.y;
	if (player.pos.y > STATG::end.y)   player.pos.y = STATG::end.y;
	debug::setString("life::%d", player.life);
	if (!player.life)debug::setString("GAME OBER");
}

void player_draw()
{
	debug::display();
	primitive::rect(player.pos.x, player.pos.y,64,64,0,0,0,1,1,1,0.8);
}

