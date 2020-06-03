#ifndef INCLUDED_COMMON
#define INCLUDED_COMMON

#define SAFE_DELETE(x)  if(x){delete x;x=NULL;}    
#define ToRadian(x)     DirectX::XMConvertToRadians(x) 
#define SCREEN_WIDTH    (1920)   // ��ʂ̕�
#define SCREEN_HEIGHT   (1080)   // ��ʂ̍���

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
////�~���[�W�b�N�p////
enum
{
	bgm1 = 0,
	Music_Max
};
//// �X�v���C�g�p ////
enum
{
	Bg = 0,
	Number,
	Effect,
	Stage,
	Spr_Max
};

#endif// ! INCLUDED_COMMON
