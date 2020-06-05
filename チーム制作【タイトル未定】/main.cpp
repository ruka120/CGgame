////�K�v�w�b�_�[�t�@�C���̃C���N���[�h
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "load.h"
using namespace GameLib;
int curScene;
int nextScene;


int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    GameLib::init(L"�E�T�M",
        SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
#if _DEBUG
	ShowCursor(TRUE);
#else
	ShowCursor(FALSE);//�J�[�\����\��
#endif  
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
				result_init();
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
			result_update();
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
			result_draw();
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
		result_end();
		break;
    }
	audio_uninit();
	spr_unload();
    GameLib::uninit();

    return 0;
}