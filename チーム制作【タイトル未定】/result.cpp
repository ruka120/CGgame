////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"


using namespace GameLib;
using namespace input;

int result_state;
extern int nextScene;
extern float fadeOut;
extern Sprite* sprData[Spr_Max];



void result_init()
{
	
	result_state = 0;
	fadeOut = 0;

}
void result_update()
{
	static const int result_max = 3;//ゲーム画面の最大数
	switch (result_state)
	{
	case 0:
		result_state++;
		break;

	case 1:
		if (TRG(0) & PAD_START)
		{
			fadeOut = 0.0f;
			result_state++;
		}
		break;

	case 2:
		fadeOut += 0.0167f;
		if (fadeOut >= 1.0f)
		{
			result_state++;
		}
		break;
	}
	if (result_state >= result_max)
	{
		nextScene = SCENE::TITLE;
	}
}


void result_draw()
{
	switch (result_state)
	{
	case 0:
	case 1:
		sprite_render(sprData[Bg],
			0, 0,
			1, 1,
			0, SCREEN_HEIGHT*2,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	break;
	case 2:
		break;
	}
	if (fadeOut > 0.0f)
	{
		primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1 - fadeOut, 1 - fadeOut, 1 - fadeOut, fadeOut);
	}
}

void result_end()
{
}



