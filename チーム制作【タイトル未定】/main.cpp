////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "title.h"
#include "game.h"
#include "load.h"
using namespace GameLib;
int curScene;
int nextScene;


int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    GameLib::init(L"ウサギ", 
        SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
	ShowCursor(FALSE);//カーソルを表示
    GameLib::setBlendMode(Blender::BS_ALPHA);
    curScene  = SCENE::TITLE;
    nextScene = SCENE::TITLE;
    title_init();
	audio_init();
	spr_load();
    while (GameLib::gameLoop())
    {
        input::update();

        if (nextScene != curScene)  
        {
            switch (curScene)      
            {
			case SCENE::TITLE:
                title_end();
                break;
			case SCENE::GAME:
                game_end();
                break;
			case SCENE::RESULT:
				break;
            }
            switch (nextScene)    
            {
			case SCENE::TITLE:
                title_init();
                break;
			case SCENE::GAME:
                game_init();
                break;
			case SCENE::RESULT:
				break;
            }
            curScene = nextScene;   
        }

        switch (curScene)
        {
		case SCENE::TITLE:
            title_update();
            break;
		case SCENE::GAME:
            game_update();
            break;
		case SCENE::RESULT:
			break;
        }

        switch (curScene)
        {
		case SCENE::TITLE:
            title_draw();
            break;
		case SCENE::GAME:
            game_draw();
            break;
		case SCENE::RESULT:
			break;
        }
        GameLib::present(1, 0);
    }
    switch (curScene)
    {
	case SCENE::TITLE:
        title_end();
        break;
	case SCENE::GAME:
        game_end();
        break;
	case SCENE::RESULT:
		break;
    }
	audio_uninit();
	spr_unload();
    GameLib::uninit();

    return 0;
}