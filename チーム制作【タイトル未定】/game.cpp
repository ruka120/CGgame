////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "stage.h"
#include "player.h"
#include "title.h"
using namespace GameLib;
using namespace input;

int game_state;    // 状態
int play_state;
int pause_select;
int pause_after;
float pause_ui_size[3];
extern int nextScene;
extern float fadeOut;

extern Sprite* sprData[Spr_Max];

enum PAUSE
{
    RedoStage,
    StageSelect,

    ReturnTitle,
    Close
};

////エフェクト関連のプロトタイプ宣言
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
    pause_select = 0;
    pause_after = 0;
    pause_ui_size[0] = 1.5;
    pause_ui_size[1] = 1;
    pause_ui_size[2] = 1;
    pause_ui_size[3] = 1;

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
             if (TRG(0) & SPACE)
             {
                 play_state = 1;
             }
             player_update();
             break;

         case 1:
             if (UP)
             {
                 pause_select--;
                 if (pause_select < 0)
                 {
                     pause_select = 3;
                 }
             }
             if (DOWN)
             {
                 pause_select++;
                 if (pause_select > 3)
                 {
                     pause_select = 0;
                 }
             }

             switch (pause_select)
             {
             case PAUSE::RedoStage:
                 pause_ui_size[0] = 1.5;
                 pause_ui_size[1] = 1;
                 pause_ui_size[2] = 1;
                 pause_ui_size[3] = 1;

                 if (TRG(0) & PAD_START) { game_init(); }
                 break;

             case PAUSE::StageSelect:
                 pause_ui_size[0] = 1;
                 pause_ui_size[1] = 1.5;
                 pause_ui_size[2] = 1;
                 pause_ui_size[3] = 1;

                 if (TRG(0) & PAD_START) { play_state++; pause_after = SCENE::SELECT; }
                 break;

             case PAUSE::ReturnTitle:
                 pause_ui_size[0] = 1;
                 pause_ui_size[1] = 1;
                 pause_ui_size[2] = 1.5;
                 pause_ui_size[3] = 1;

                 if (TRG(0) & PAD_START) { play_state++; pause_after = SCENE::TITLE; }
                 break;

             case PAUSE::Close:
                 pause_ui_size[0] = 1;
                 pause_ui_size[1] = 1;
                 pause_ui_size[2] = 1;
                 pause_ui_size[3] = 1.5;
                 if (TRG(0) & PAD_START) { play_state = 0; }
                 break;
             }
             break;

         case 2:
             fadeOut += 0.0167f;
             if (fadeOut >= 1.0f)
             {
                 nextScene = pause_after;
             }
             break;
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
    if (play_state == 1)
    {
        sprite_render(sprData[Bg],
            480, 270,
            0.5, 0.5,
            0, 3240,
            SCREEN_WIDTH, SCREEN_HEIGHT);

        //ステージをやり直す //80~160
        sprite_render(sprData[Pause],
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150,
            pause_ui_size[0], pause_ui_size[0],
            0, 80,
            960, 80,
            480, 40);

        //ステージ選択 //200~280
        sprite_render(sprData[Pause],
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20,
            pause_ui_size[1], pause_ui_size[1],
            0, 200,
            960, 80,
            480, 40);

        //タイトルへ戻る //310~390
        sprite_render(sprData[Pause],
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100,
            pause_ui_size[2], pause_ui_size[2],
            0, 310,
            960, 80,
            480, 40);

        //閉じる //410~490
        sprite_render(sprData[Pause],
            SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 210,
            pause_ui_size[3], pause_ui_size[3],
            0, 410,
            960, 80,
            480, 40);
    }
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



