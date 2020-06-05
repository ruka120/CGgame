#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "player.h"

#include "stage.h"

using namespace GameLib;
using namespace input;
enum MOVE_VECTOR//移動方向
{
	Stop=0,
	Right,
	Left,
	Up,
	Down,
};
//移動フラグ
//int XorY -> ｘ方向に動くかｙ方向に動くか(x->0,y->1)
//float distance -> 移動距離
//int time -> 何フレームかけて移動するか
void PLAYER::move(float distance,int time)
{
	static int count = 0;
	switch (move_vector)
	{
	default://移動方向以外が入っていたら終了
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
	
	//移動
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
	//移動回数のリセット
	if (TRG(0)&PAD_F1) { reset(); }
#endif
	//移動制限
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

