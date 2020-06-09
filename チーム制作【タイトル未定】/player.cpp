#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "stage.h"
#include "player.h"

using namespace GameLib;
using namespace input;
enum MOVE_VECTOR//移動方向
{
	Stop = 0,
	Right,
	Left,
	Up,
	Down,
};
enum PLAYER_STATE
{
	GAME_OVER = -1,
	Think = 0,
	Move,
	Bounce_block,

};

//移動フラグ
//int XorY -> ｘ方向に動くかｙ方向に動くか(x->0,y->1)
//float distance -> 移動距離
//int time -> 何フレームかけて移動するか
void PLAYER::move(int time)
{
	static int count = 0;
	switch (move_vector)
	{
	default://移動方向以外が入っていたら終了
		return;
	case MOVE_VECTOR::Left:
		pos.x -= ((get_Cpos(chip_num.x, chip_num.y).x - get_Cpos(chip_num.x-1, chip_num.y).x)/ time);
		count++;
		break;
	case MOVE_VECTOR::Right:
		pos.x += ((get_Cpos(chip_num.x+1, chip_num.y).x - get_Cpos(chip_num.x, chip_num.y).x) / time);
		count++;
		break;
	case MOVE_VECTOR::Up:
		pos.y -= ((get_Cpos(chip_num.x, chip_num.y).y - get_Cpos(chip_num.x, chip_num.y-1).y) / time);
		count++;
		break;
	case MOVE_VECTOR::Down:
		pos.y += ((get_Cpos(chip_num.x, chip_num.y+1).y - get_Cpos(chip_num.x, chip_num.y ).y) / time);
		count++;
		break;
	}
	if (count == time)
	{
		state = PLAYER_STATE::Think;
		life--;
		chip_num = get_nowCnum(center);
		count = 0;
	}
}
namespace STATG
{
	VECTOR2 end;
	VECTOR2 start;
}

void PLAYER::reset()
{
	state = PLAYER_STATE::Think;
	pos = Pstart();
	life = 16;
	center = { pos.x + 32,pos.y + 32 };
	chip_num = get_nowCnum(center);
	move_vector = MOVE_VECTOR::Stop;
}

void PLAYER::init()
{
	state = PLAYER_STATE::Think;
	pos = Pstart();
	STATG::start = Sstart();
	STATG::end = Send();
	life = 16;
	center = { pos.x + 32,pos.y + 32 };
	chip_num = get_nowCnum(center);
	move_vector = MOVE_VECTOR::Stop;

}
#if (_DEBUG)
void PLAYER::STATUS()
{
	debug::setString("///// STATUS /////");
	debug::setString(" life  [%d]",life);
	debug::setString(" POS  [%d][%d]", chip_num.x, chip_num.y);
	if (STATE(0)&PAD_RIGHT){ debug::setString("THE KEY BEING PRESSED [RIGHT]");}
	else debug::setString("");
	if (STATE(0)&PAD_LEFT) { debug::setString("THE KEY BEING PRESSED [LEFT]"); }
	else debug::setString("");
	if (STATE(0)&PAD_UP)   { debug::setString("THE KEY BEING PRESSED [UP]");   }
	else debug::setString("");
	if (STATE(0)&PAD_DOWN) { debug::setString("THE KEY BEING PRESSED [DOWN]"); }
	else debug::setString("");
	debug::setString(" GIMMICK HIT FLG");
	debug::setString(" 0->TRUE 1->FALSE");
	debug::setString(" RIGHT [%d]", G_hit(CHIP_NUM{ chip_num.x + 1, chip_num.y }));
	debug::setString(" LEFT  [%d]", G_hit(CHIP_NUM{ chip_num.x - 1, chip_num.y }));
	debug::setString(" UP    [%d]", G_hit(CHIP_NUM{ chip_num.x, chip_num.y - 1 }));
	debug::setString(" DOWN  [%d]", G_hit(CHIP_NUM{ chip_num.x, chip_num.y + 1 }));
	if (state == PLAYER_STATE::GAME_OVER)
	{
		debug::setString("////////////////////////");
		debug::setString("/////  GAME  OVER  /////");
		debug::setString("////////////////////////");
	}
	else
	{
		debug::setString("");
		debug::setString("");
		debug::setString("");
	}
}
#endif
void PLAYER::update()
{
	center = { pos.x + 32,pos.y + 32 };

	switch (state)
	{
	default:
		break;
	case PLAYER_STATE::Think:
		if(move_vector != MOVE_VECTOR::Stop)move_vector = MOVE_VECTOR::Stop;
		//移動
		if (life)
		{
			if (RIGHT&&get_Ctype(chip_num.x + 1, chip_num.y) != STAGE_TYPE::Wall && !G_hit(CHIP_NUM{chip_num.x + 1, chip_num.y})) { state = PLAYER_STATE::Move; move_vector = MOVE_VECTOR::Right; }
			if (LEFT &&get_Ctype(chip_num.x - 1, chip_num.y) != STAGE_TYPE::Wall && !G_hit(CHIP_NUM{chip_num.x - 1, chip_num.y})) { state = PLAYER_STATE::Move; move_vector = MOVE_VECTOR::Left;  }
			if (UP   &&get_Ctype(chip_num.x, chip_num.y - 1) != STAGE_TYPE::Wall && !G_hit(CHIP_NUM{chip_num.x, chip_num.y - 1})) { state = PLAYER_STATE::Move; move_vector = MOVE_VECTOR::Up;    }
			if (DOWN &&get_Ctype(chip_num.x, chip_num.y + 1) != STAGE_TYPE::Wall && !G_hit(CHIP_NUM{chip_num.x, chip_num.y + 1})) { state = PLAYER_STATE::Move; move_vector = MOVE_VECTOR::Down;  }

		}
		else if (RIGHT | LEFT | UP | DOWN)
		{
			state = PLAYER_STATE::GAME_OVER;
		}
		break;
	case PLAYER_STATE::Move:
		switch (move_vector)
		{
		   case MOVE_VECTOR::Left:
		   case MOVE_VECTOR::Right:
		   	    move(30);
		   	    break;
		   case MOVE_VECTOR::Up:
		   case MOVE_VECTOR::Down:
		   	    move(30);
		   	    break;
		}
		break;
	}
#if (_DEBUG)
	STATUS();
#endif
#if (_DEBUG)//デバッグ用復活ボタン
//移動回数のリセット
	if (TRG(0)&PAD_F1) { reset(); }
#endif // (_DEBUG)

	
	//移動制限
	if (pos.x < STATG::start.x) pos.x = STATG::start.x;
	if (pos.x > STATG::end.x)   pos.x = STATG::end.x;
	if (pos.y < STATG::start.y) pos.y = STATG::start.y;
	if (pos.y > STATG::end.y)   pos.y = STATG::end.y;
}

void PLAYER::draw()
{
#if(_DEBUG)
	debug::display();
#endif
	primitive::rect(pos.x, pos.y, 64, 64, 0, 0, 0, 1, 1, 1, 0.8);
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
