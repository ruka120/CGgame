////�K�v�w�b�_�[�t�@�C���̃C���N���[�h
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "load.h"
using namespace GameLib;
//���y�ǂݍ���
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
	//���y�̉������
	int i;
	for (i = 0; i < Music_Max; i++)
		music::unload(i);
}

//�摜�ǂݍ���
Sprite* sprData[Spr_Max];
wchar_t* sprName[] =
{
	L"./Data/Images/bg.png",     //�w�i
	L"./Data/Images/number.png", //����
	L"./Data/Images/number.png", //�G�t�F�N�g(number.png�ŉ��u��)
	L"./Data/Images/mapchip.png" //�X�e�[�W(�}�b�v�`�b�v)
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
