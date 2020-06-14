#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "title.h"
#include "stage.h"
#include "stage_select.h"
using namespace GameLib;
using namespace input;

extern int nextScene;
extern Sprite* sprData[Spr_Max];

VECTOR2 cursor_pos;
int     stage_num;
int     select_state;

enum STAGE_NUM
{
    Zero,
    First,
    Second,
    Third,
    Fourth,
    Fifth,
};

void select_init()
{
    cursor_pos = { 960,100 };
    stage_num = STAGE_NUM::First;
}

void select_update()
{
    switch (select_state)
    {
    case 0:
        select_state++;
        break;

    case 1:
        switch (stage_num)
        {
        case STAGE_NUM::First:
            cursor_pos = { 960,100 };
            if (DOWN)
            {
                //cursor_pos.x += 100;
                //cursor_pos.y += 100;
                //if (cursor_pos.x > 1500 || cursor_pos.y > 400)
                //{
                    cursor_pos = { 1100,400 };
                    stage_num = 2;
                //}
            }
            if (TRG(0) & PAD_START)
            {
                nextScene = SCENE::GAME;
                stage_init();
            }
            break;
        }

    case 2:
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::TITLE;
        }
        break;
       /* if (UP)
        {
            stage_num--;
            if (stage_num < 0) { stage_num = 0; }
        }
        if (DOWN)
        {
            stage_num++;
            if (stage_num > 5) { stage_num = 5; }
        }
        if (TRG(0) & PAD_START)
        {
            nextScene = SCENE::GAME;
            switch (stage_num)
            {
            case STAGE_NUM::First:
                stage_init();
                break;

            case STAGE_NUM::Second:
                nextScene = SCENE::TITLE;
                break;

            }
            select_state++;
        }
        break;

    case 2:
        break;*/
    }
}

void select_draw()
{
    sprite_render(sprData[Stage_select],
        0, 0,
        1, 1,
        0, 0,
        SCREEN_WIDTH, SCREEN_HEIGHT);

    sprite_render(sprData[Cursor],
        cursor_pos.x, cursor_pos.y,
        1, 1,
        0, 0,
        64, 64);
}

void select_end()
{

}