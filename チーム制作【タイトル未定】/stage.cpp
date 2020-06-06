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
/***************************ステージ*********************************/
/********************************************************************/
void STAGE::init(INITIAL_VALUE value)
{
	//変数の初期化
	size = value.size;
	useX = value.useX;
	useY = value.useY;
	Pspawn = value.Pstart;
	//開始位置の設定
	start = {((SCREEN_WIDTH / 2) - (size.x*(useX/2))),((SCREEN_HEIGHT / 2) - (size.y*(useY / 2))) };
	//ステージデータ
	FILE* fp;
	fp = fopen(value.fname, "r");
	if(!fp)return;
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
	return VECTOR2{ start.x +(size.x*numX),start.y + (size.y*numY) };
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
	pos = { (((SCREEN_WIDTH / 2) - (size.x*(useX / 2)))+(size.x*Pspawn.x)),(((SCREEN_HEIGHT / 2) - (size.y*(useY / 2))) + (size.y*Pspawn.y)) };
	return pos;
}

VECTOR2 STAGE::Sstart()
{
	return start;
}

VECTOR2 STAGE::Send()
{
	return VECTOR2{ start.x+(size.x*(useX-1)),start.y + (size.y*(useY-1)) };
}

void STAGE::draw()
{
	extern Sprite* sprData[Spr_Max];
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			sprite_render(sprData[Stage], start.x + (size.x*x), start.y + (size.y*y), 1, 1, size.x*(data[y][x]%X), size.y*(data[y][x]/X),64,64);
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
				return CHIP_NUM{x,y};
			}
		}
	}

	return CHIP_NUM();

}
STAGE stage;
INITIAL_VALUE stage1=
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
//現在のマップチップ上での番号取得関数
//Rect rect -> 現在の四隅の座標
CHIP_NUM get_nowCnum(VECTOR2 pos)
{
	return stage.get_nowCnum(pos);
}
//プレイヤーの開始位置取得関数
VECTOR2 Pstart()
{
	return stage.Pstart();
}
//ステージの開始位置取得関数
VECTOR2 Sstart()
{
		return stage.Sstart();
}
//ステージの終了位置取得関数
VECTOR2 Send()
{
		return stage.Send();
}
//指定されたチップ番号の座標を返す関数
//int numX -> マップチップのX番号
//int numY -> マップチップのY番号
VECTOR2 get_Cpos(int numX,int numY)
{
	return stage.get_pos(numX, numY);
}

VECTOR2 get_Csize()
{
	return stage.get_size();
}
//指定されたチップ番号の種類を返す関数
//int numX -> マップチップのX番号
//int numY -> マップチップのY番号
int get_Ctype(int numX, int numY)
{
	return stage.get_type(numX, numY);
}



/********************************************************************/
/***************************ギミック*********************************/
/********************************************************************/

#if _DEBUG
VECTOR4 color[]//ギミック用画像の代わり
{
	{1,1,1,1},//白
	{0,0,0,1},//黒
	{1,0,0,1},//赤
	{0,1,0,1},//緑
	{0,0,1,1},//青
};
#endif
GIMMICK_DATA test[]
={
	{0,0,0},
	{1,2,0},
	{2,5,3},
	{3,7,6},
	{4,2,6},
    {-1,0,0}
};

void GIMMICK::init(GIMMICK_DATA data)
{
	type = data.type;
	pos = stage.get_pos(data.first.x, data.first.y);
}

void GIMMICK::draw()
{
#if _DEBUG
	primitive::rect(VECTOR2{ pos.x,pos.y }, VECTOR2{ 64,64 }, VECTOR2{ 0,0 },0, color[type]);
#endif // _DEBUG

}

static const int gimmick_max=8;//使えるギミックの最大数
int use_gimmick_num;//実際に使うギミックの個数
GIMMICK gimmick[gimmick_max];

void gimmick_init()
{
	use_gimmick_num = 0;
	for (int i = 0; i < gimmick_max; i++)
	{
		if (test[i].type == GIMMICK_TYPE::END)break;
		gimmick[i].init(test[i]);
		use_gimmick_num++;//実際に使う個数のカウント
	}
}

void gimmick_update()
{

}

void gimmick_draw()
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		gimmick[i].draw();
	}
}
