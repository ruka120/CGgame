////�K�v�w�b�_�[�t�@�C���̃C���N���[�h
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "stage.h"
#include "player.h"
using namespace GameLib;
using namespace input;

int game_state;    // ���
int play_state;
int pose_select;
extern int nextScene;
extern float fadeOut;
extern Sprite* sprData[Spr_Max];

////�G�t�F�N�g�֘A�̃v���_�N�g�錾
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
    pose_select = 0;
	fadeOut = 0;
	EFFECT::init();
	player_init();
	gimmick_init();
}
void game_update()
{
	static const int game_max = 3;//�Q�[����ʂ̍ő吔
    switch (game_state)
    {
     case 0:
         game_init();
         game_state++;
         break;
     
     case 1:
         player_update();
         if (TRG(0) & SPACE)
         {
             play_state = 1;
         }
         if (TRG(0) & PAD_START)
         {
             game_state = 2;
         }
         /*switch (play_state)
         {
         case 0:
             if (TRG(0) & SPACE)
             {
                 play_state = 1;
             }
             player_update();
         break;

         case 1:
             if (TRG(0) & PAD_UP)
             {
                 pose_select--;
                 if (pose_select < 0)
                 {
                     pose_select = 2;
                 }
             }
             if (TRG(0) & PAD_DOWN)
             {
                 pose_select++;
                 if (pose_select > 2)
                 {
                     pose_select = 0;
                 }
             }
             if (TRG(0) & PAD_START)
             {
                 switch (pose_select)
                 {
                 case 1:
                     pose_select = 0;
                     game_state = 2;
                     break;

                 case 2:
                     pose_select = 0;
                     play_state = 0;
                     break;
                 }
             }*/
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
        sprite_render(sprData[Pose], 0, 0, 1, 1, 0, 0, 960, 540, 480, 270);
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

void game_end()//�摜�̔j��
{
}



