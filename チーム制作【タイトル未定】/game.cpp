////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "stage.h"
#include "player.h"
using namespace GameLib;
using namespace input;

int game_state;    // 状態

int game_score;
int play_state;    //ポーズ画面(タイトル戻る、やり直す、ゲームを続けるの選択肢作るかな)

extern int nextScene;
extern float fadeOut;
extern Sprite* sprData[Spr_Max];

////エフェクト関連のプロダクト宣言
namespace EFFECT
{
	void init();
	void draw();
}

void game_init()
{
	stage_init();
    game_state = 0;

    play_state = 0;

	fadeOut = 0;
	EFFECT::init();
	player_init();
	gimmick_init();
}
void game_update()
{
	static const int game_max = 3;//ゲーム画面の最大数
    switch (game_state)
    {
     case 0:
         game_state++;
         break;
     
     case 1:
         switch (play_state)
         {
         case 0:
             if (TRG(0) & PAD_START)
             {
                 fadeOut = 0.0f;
                 game_state++;
             }
		 player_update();
         break;

         case 1:

         }
    break;
     
     case 2:
         fadeOut += 0.0167f;
         if (fadeOut >= 1.0f)
         {
             game_state++;
         }
         break;
    }
    if (game_state >= game_max) 
    {
		nextScene = SCENE::RESULT;
    }
}


void game_draw()
{
	switch (game_state)
	{
	case 0:
	case 1:
		sprite_render(sprData[Bg],
			0, 0,
			1, 1,
			0, SCREEN_HEIGHT,
			SCREEN_WIDTH, SCREEN_HEIGHT);
		stage_draw();
		player_draw();
		gimmick_draw();
	EFFECT::draw();
		
		break;
	case 2:
		break;
	}
	if (fadeOut > 0.0f)
	{
		primitive::rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 0, 1-fadeOut, 1 - fadeOut, 1-fadeOut, fadeOut);
	}
}

void game_end()//画像の破棄
{
}



