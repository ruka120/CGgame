#ifndef INCLUDED_COMMON
#define INCLUDED_COMMON

#define SAFE_DELETE(x)  if(x){delete x;x=NULL;}    
#define ToRadian(x)     DirectX::XMConvertToRadians(x) 
#define SCREEN_WIDTH    (1920)   // 画面の幅
#define SCREEN_HEIGHT   (1080)   // 画面の高さ
struct Rect
{
	float top;
	float under;
	float left;
	float right;
};
enum SCENE
{
	TITLE=0,
	GAME,
	RESULT,
};
#if(false)
#define UP    (STATE(0)&PAD_UP)
#define DOWN  (STATE(0)&PAD_DOWN)
#define LEFT  (STATE(0)&PAD_LEFT)
#define RIGHT (STATE(0)&PAD_RIGHT)
#endif
////ミュージック用////
enum
{
	bgm1 = 0,
	Music_Max
};
//// スプライト用 ////
enum
{
	Bg = 0,
	Number,
	Effect,
	Stage,
	Spr_Max
};

#endif// ! INCLUDED_COMMON
