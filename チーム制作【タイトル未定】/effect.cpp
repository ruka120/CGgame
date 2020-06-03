////�K�v�w�b�_�[�t�@�C���̃C���N���[�h
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "effect.h"
using namespace GameLib;
extern Sprite* sprData[Spr_Max];
//�G�t�F�N�g�֘A
bool isPause;
struct EFFECT_DATA//�f�[�^�\����
{
//�������K�v
	int time;             //�؂�ւ�����
	int NumX;             //�`�b�v�̉��̌�
	int NumY;             //�`�b�v�̏c�̌�
	int max;              //�`�b�v�̑���
	float sclx;           //�X�P�[���iX�j
	float scly;           //�X�P�[���iY�j
	float dataposx;       //�摜�f�[�^�̊J�nX���W
	float dataposy;       //�摜�f�[�^�̊J�nY���W
	float sizex;          //�P�`�b�v�̉��̑傫��
	float sizey;          //�P�`�b�v�̏c�̑傫��

};
struct DATA 
{
	EFFECT_DATA data;
};
EFFECT_DATA data1 =//�G�t�F�N�g(1��)
{

};
DATA fx[Effect_Max]=
{
	data1
};
class FX //�G�t�F�N�g�N���X
{
private:
	int timer;
	VECTOR2 pos;
	int x;
	int y;
	int count;
	int data_num;//�G�t�F�N�g�ԍ�
public:
	bool exist = false;//���݃t���O
	bool init(int effect_num, float posx, float posy)
	{
		if (exist)return true;//���݂��Ă�����I��
		//������
		{
			pos = { posx,posy };
			data_num = effect_num;
			exist = true;
			x = 0;
			y = 0;
			count = 1;
			timer = 0;
		}
		return false;
	}
	void draw()
	{
		if (!isPause)
		{
			if (timer != 0 && timer%fx[data_num].data.time == 0)
			{
				x++;
				count++;
				if (x >= fx[data_num].data.NumX)
				{
					x = 0;
					y++;
				}
				if (count > fx[data_num].data.max)
				{
					exist = false;
					return;
				}
			}
		}
		sprite_render
		(
			sprData[Effect],
			pos.x, pos.y,
			fx[data_num].data.sclx, fx[data_num].data.scly,
			fx[data_num].data.dataposx + (fx[data_num].data.sizex*x), fx[data_num].data.dataposy + (fx[data_num].data.sizey*y),
			fx[data_num].data.sizex, fx[data_num].data.sizey,
			fx[data_num].data.sizex/2, fx[data_num].data.sizey/2,
			0, 
			1, 1, 1, 1
		);
		timer++;

	}
};
namespace EFFECT
{
	static const int effect_max = 32;
	
	FX effect[effect_max];
	void init()
	{
		for (int i = 0; i < effect_max; i++)
		{
			if (!effect[i].exist)continue;
			effect[i].exist = false;
		}
	}
	void set(int num, float posx, float posy)
	{
		for (int i = 0; i < effect_max; i++)
		{
			//�g���Ă�����X�L�b�v
			if (effect[i].init(num, posx, posy))continue;
			break;
		}
	}
	void set(int num, VECTOR2 pos)
	{
		for (int i = 0; i < effect_max; i++)
		{
			//�g���Ă�����X�L�b�v
			if (effect[i].init(num, pos.x, pos.y))continue;
			break;
		}
	}
	void pause(bool isFlg)
	{
		isPause = isFlg;
	}
	void draw()
	{
		for (int i = 0; i < effect_max; i++)
		{
			if (effect[i].exist)
			{
				effect[i].draw();
			}
		}
	}
}
