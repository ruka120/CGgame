#define	_CRT_SECURE_NO_WARNINGS
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
using namespace GameLib;
#include "common.h"
#include "add_on.h"
#include "stage.h"
/********************************************************************/
/***************************�X�e�[�W*********************************/
/********************************************************************/
void STAGE::init(INITIAL_VALUE value)
{
	//�ϐ��̏�����
	size = value.size;
	useX = value.useX;
	useY = value.useY;
	Pspawn = value.Pstart;
	//�J�n�ʒu�̐ݒ�
	start = { ((SCREEN_WIDTH / 2) - (size.x*(useX / 2))),((SCREEN_HEIGHT / 2) - (size.y*(useY / 2))) };
	//�X�e�[�W�f�[�^
	FILE* fp;
	fp = fopen(value.fname, "r");
	if (!fp)return;
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			fscanf(fp, "%d,", &data[y][x]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

}

VECTOR2 STAGE::get_pos(int numX, int numY)
{
	return VECTOR2{ start.x + (size.x*numX),start.y + (size.y*numY) };
}

VECTOR2 STAGE::get_size()
{
	return size;
}

int STAGE::get_type(int numX, int numY)
{
	return data[numX][numY];
}

VECTOR2 STAGE::Pstart()
{
	VECTOR2 pos;
	pos = { (((SCREEN_WIDTH / 2) - (size.x*(useX / 2))) + (size.x*Pspawn.x)),(((SCREEN_HEIGHT / 2) - (size.y*(useY / 2))) + (size.y*Pspawn.y)) };
	return pos;
}

VECTOR2 STAGE::Sstart()
{
	return start;
}

VECTOR2 STAGE::Send()
{
	return VECTOR2{ start.x + (size.x*(useX - 1)),start.y + (size.y*(useY - 1)) };
}

void STAGE::draw()
{
	extern Sprite* sprData[Spr_Max];
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			sprite_render(sprData[Stage], start.x + (size.x*x), start.y + (size.y*y), 1, 1, size.x*(data[y][x] % X), size.y*(data[y][x] / X), 64, 64);
		}
	}
}
CHIP_NUM STAGE::get_nowCnum(VECTOR2 pos)
{
	static Rect Crect;
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			Crect = { (start.y + (size.y*y)),(start.y + (size.y*(y + 1))),(start.x + (size.x*x)),(start.x + (size.x*(x + 1))) };
			if (Judge.rect(Crect, pos))
			{
				return CHIP_NUM{ x,y };
			}
		}
	}

	return CHIP_NUM();

}
STAGE stage;
INITIAL_VALUE stage1 =
{
	"DATA\\MAP\\test.txt",
	8,
	8,
	{64,64},
	{2,3},
};
void stage_init()
{
#if(true)
	stage.init(stage1);
#else
	switch (stage_num)
	{
	default:
		break;
	case 0:
		stage.init(stage1);
		break;
	}
#endif
}

void stage_update()
{

}

void stage_draw()
{
	stage.draw();
}
//���݂̃}�b�v�`�b�v��ł̔ԍ��擾�֐�
//Rect rect -> ���݂̎l���̍��W
CHIP_NUM get_nowCnum(VECTOR2 pos)
{
	return stage.get_nowCnum(pos);
}
//�v���C���[�̊J�n�ʒu�擾�֐�
VECTOR2 Pstart()
{
	return stage.Pstart();
}
//�X�e�[�W�̊J�n�ʒu�擾�֐�
VECTOR2 Sstart()
{
	return stage.Sstart();
}
//�X�e�[�W�̏I���ʒu�擾�֐�
VECTOR2 Send()
{
	return stage.Send();
}
//�w�肳�ꂽ�`�b�v�ԍ��̍��W��Ԃ��֐�
//int numX -> �}�b�v�`�b�v��X�ԍ�
//int numY -> �}�b�v�`�b�v��Y�ԍ�
VECTOR2 get_Cpos(int numX, int numY)
{
	return stage.get_pos(numX, numY);
}

VECTOR2 get_Csize()
{
	return stage.get_size();
}
//�w�肳�ꂽ�`�b�v�ԍ��̎�ނ�Ԃ��֐�
//int numX -> �}�b�v�`�b�v��X�ԍ�
//int numY -> �}�b�v�`�b�v��Y�ԍ�
int get_Ctype(int numX, int numY)
{
	return stage.get_type(numX, numY);
}



/********************************************************************/
/***************************�M�~�b�N*********************************/
/********************************************************************/

#if GIMMICK_TEST
VECTOR4 color[]//�M�~�b�N�p�摜�̑���
{
	{0,0,0,0},//�����Ȃ�
	{1,1,1,1},//��
	{0,0,0,1},//��
	{1,0,0,1},//��
	{0,1,0,1},//��
	{0,0,1,1},//��
};
GIMMICK_DATA test[]
= {
	{1,0,0},
	{2,2,0},
	{3,5,3},
	{4,7,6},
	{5,2,6},
	{-1,0,0}
};
#endif

void GIMMICK::init(GIMMICK_DATA data)
{
	type   = data.type;
	pos    = stage.get_pos(data.first.x, data.first.y);
	center = pos + VECTOR2{32,32};
	exist  = true;
}

bool GIMMICK::hit(CHIP_NUM now_num)
{
	if (get_nowCnum(center).x == now_num.x&&get_nowCnum(center).y == now_num.y)
	{
		//switch (type)//�e�^�C�v���Ƃ̍X�V�����p�̏�����
		//{
		//default:
		//	break;
		//}
		return true;
	}
	return false;
}

void GIMMICK::update()
{
	switch (type)
	{
	default:
		return;
#if(GIMMICK_TEST)//�e�X�g�p
	case GIMMICK_TYPE::White:

		break;
	case GIMMICK_TYPE::Bloac:

		break;
	case GIMMICK_TYPE::Red:

		break;
	case GIMMICK_TYPE::Green:

		break;
	case GIMMICK_TYPE::Blue:

		break;
#endif
	}
}

void GIMMICK::draw()
{
#if (GIMMICK_TEST)
	primitive::rect(VECTOR2{ pos.x,pos.y }, VECTOR2{ 64,64 }, VECTOR2{ 0,0 }, 0, color[type]);
#endif // _DEBUG

}

static const int gimmick_max = 8;//�g����M�~�b�N�̍ő吔
int use_gimmick_num;//���ۂɎg���M�~�b�N�̌�
GIMMICK gimmick[gimmick_max];

void gimmick_init()
{
	use_gimmick_num = 0;
	for (int i = 0; i < gimmick_max; i++)
	{
		if (test[i].type == GIMMICK_TYPE::END)break;
		gimmick[i].init(test[i]);
		use_gimmick_num++;//���ۂɎg�����̃J�E���g
	}
}

void gimmick_update()
{
	for (int i = 0; i < gimmick_max; i++)
	{
		if (!gimmick[i].get_exist()) continue;//���݂��Ă��Ȃ��Ȃ�X�L�b�v
		gimmick[i].update();
	}
}

void gimmick_draw()
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		if (!gimmick[i].get_exist()) continue;//���݂��Ă��Ȃ��Ȃ�X�L�b�v
		gimmick[i].draw();
	}
}



// �M�~�b�N�Ɠ����������̔���
// CHIP_NUM now_num ->�@���݂̃}�b�v�`�b�v��̔ԍ�
//�@�Ԃ�l�@->�@���������M�~�b�N�̃^�C�v���͂O(�����������Ă��Ȃ�)
//���݂̂Ƃ������Ă邯�ǎg������
//�L�[���͂��ꂽ�Ƃ��̈ړ���̃`�b�v������
//�ړ���œ����邩�ǂ���������p�̊֐�
int G_hit(CHIP_NUM now_num)
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		if (!gimmick[i].get_exist()) continue;//���݂��Ă��Ȃ��Ȃ�X�L�b�v
		if (gimmick[i].hit(now_num))return gimmick[i].get_type();
	}
	return 0;//�����������Ă��Ȃ�
}

void G_destroy(CHIP_NUM now_num)
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		if (!gimmick[i].get_exist()) continue;//���݂��Ă��Ȃ��Ȃ�X�L�b�v
		if (gimmick[i].hit(now_num))
		{
			gimmick[i].destroy();
		}
	}
}