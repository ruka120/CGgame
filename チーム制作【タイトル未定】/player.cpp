#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "player.h"
#include "add_on.h"
#include "stage.h"

using namespace GameLib;
using namespace input;
OBJ player;
int life;
namespace STATG
{
 VECTOR2 end;
 VECTOR2 start;
}
void reset()
{
	player.pos = { Pstart(0).x,Pstart(0).y };
	life = 16;
}
void player_init()
{
	player.pos = { Pstart(0).x,Pstart(0).y };
	STATG::start = Sstart(0);
	STATG::end = Send(0);
	life = 16;
}

void player_update()
{
	//ˆÚ“®
	if(life)
	{ 
	if (TRG(0)&PAD_RIGHT){player.pos.x += 64;life--;}
	if (TRG(0)&PAD_LEFT) {player.pos.x -= 64;life--;}
	if (TRG(0)&PAD_DOWN) {player.pos.y += 64;life--;}
	if (TRG(0)&PAD_UP)   {player.pos.y -= 64;life--;}
	}
	//ˆÚ“®‰ñ”‚ÌƒŠƒZƒbƒg
	if (TRG(0)&PAD_F1) { reset(); }
	//ˆÚ“®§ŒÀ
	if (player.pos.x < STATG::start.x)player.pos.x = STATG::start.x;
	if (player.pos.x + 64 > STATG::end.x) player.pos.x = STATG::end.x;
	if (player.pos.y < STATG::start.y)player.pos.y = STATG::start.y;
	if (player.pos.y + 64 > STATG::end.y) player.pos.y = STATG::end.y;
	debug::setString("life::%d", life);
	if (!life)debug::setString("GAME OBER");
}

void player_draw()
{
	debug::display();
	primitive::rect(player.pos.x, player.pos.y,64,64,0,0,0,1,1,1,0.8);
}