////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "load.h"
using namespace GameLib;
//音楽読み込み
wchar_t* MusicName[] =
{
	L"./Data/Musics/bgm1.wav",
};
void audio_init()
{
	for (int i = 0; i < Music_Max; i++)
	{
		music::load(i, MusicName[i], 0.3f);
    }
	sound::load(L"./Data/Sounds/se.xwb");//SE
}
void audio_uninit()
{
	//音楽の解放処理
	int i;
	for (i = 0; i < Music_Max; i++)
		music::unload(i);
}

//画像読み込み
Sprite* sprData[Spr_Max];
wchar_t* sprName[] =
{
	L"./Data/Images/bg.png",     //背景
	L"./Data/Images/title.png",//タイトル用文字
	L"./Data/Images/number.png", //数字
	L"./Data/Images/number.png", //エフェクト(number.pngで仮置き)
	L"./Data/Images/pause.png", //ポーズ
    L"./Data/Images/stage_select.png", //ステージセレクト
    L"./Data/Images/cursor.png", //カーソル
	L"./Data/Images/mapchip.png" //ステージ(マップチップ)
};
void spr_load()
{
	for (int i = 0; i < Spr_Max; i++)
	{
		sprite_load(&sprData[i], sprName[i]);
	}
}
void spr_unload()
{
	for (int i = 0; i < Spr_Max; i++)
	{
		SAFE_DELETE(sprData[i]);
	}
}
