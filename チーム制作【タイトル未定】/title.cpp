////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
using namespace GameLib;
using namespace input;
int title_state;      // 状態
int title_timer;      // タイマー
float fadeOut;        // フェイドアウト
extern int nextScene; //シーン移行用
extern Sprite* sprData[Spr_Max];
void title_init()
{
	fadeOut = 0;
    title_state = 0;
    title_timer = 0;
}

void title_update()
{
	static const int title_max=3;//タイトル場面の最大数
    switch (title_state)
    {
    case 0:
		music::play(0, true);
        title_state++;
        break;
    case 1:
        if (TRG(0) & PAD_START)
        {
            fadeOut=0.0f;
            title_state++;
        }
        break;
    case 2:
        fadeOut += 0.0167f;
        if (fadeOut >= 1.0f)
        {  title_state++; }
        break;
    }
    if (title_state == title_max) 
    { nextScene = SCENE::GAME; }
    title_timer++;
   }

void title_draw()
{
	switch (title_state)
	{
	case 0:
	case 1:
		sprite_render(sprData[Bg],
			0, 0,
			1, 1,
			0, 0,
			SCREEN_WIDTH, SCREEN_HEIGHT);
		break;
	case 2:
		break;
	}
		if (fadeOut > 0.0f)
		{
			primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1- fadeOut, 1 - fadeOut, 1 - fadeOut, fadeOut);
		}
}

void title_end()
{

}



