////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
using namespace GameLib;
using namespace input;
int title_state;      // 状態
float fadeOut;        // フェイドアウト
extern int nextScene; //シーン移行用
extern Sprite* sprData[Spr_Max];
int play_exit;
enum PLAYorEXIT
{
	PLAY = 0,
	EXIT,
};
float title_ui_size[2];
void title_init()
{
	play_exit = PLAYorEXIT::PLAY;
	title_ui_size[0] = 2;
	title_ui_size[1] = 1;
	fadeOut = 0;
    title_state = 0;
}
void title_update()
{
	static const int title_max=3;//タイトル場面の最大数
    switch (title_state)
    {
    case 0:
        title_state++;
        break;
    case 1:
		if(UP||DOWN)
		{
			switch (play_exit)
			{
			default:
				break;
			case PLAYorEXIT::PLAY:
				play_exit = PLAYorEXIT::EXIT;
				title_ui_size[0] = 1;
				title_ui_size[1] = 2;
				break;
			case PLAYorEXIT::EXIT:
				play_exit = PLAYorEXIT::PLAY;
				title_ui_size[0] = 2;
				title_ui_size[1] = 1;
				break;
			}
		}
		
        if (TRG(0) & PAD_START)
        {
			switch (play_exit)
			{
			default:
				break;
			case PLAYorEXIT::PLAY:
				fadeOut = 0.0f;
				title_state++;//ゲームへ
				break;
			case PLAYorEXIT::EXIT:
				std::exit(0);//正常終了
				break;
			}
        }
        break;
    case 2:
        fadeOut += 0.0167f;
        if (fadeOut >= 1.0f)
        {  title_state++; }
        break;
    }
    if (title_state >= title_max) 
    { nextScene = SCENE::GAME; }
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
		sprite_render(sprData[Title],//PLAY TO GAME
			SCREEN_WIDTH/2, (SCREEN_HEIGHT/2)+300,
			title_ui_size[0], title_ui_size[0],
			0,0,
			300,50,150,25);
		sprite_render(sprData[Title],//EXIT
			SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 400,
			title_ui_size[1], title_ui_size[1],
			0, 50,
			300, 50, 150, 25);
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



