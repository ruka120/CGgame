#define	_CRT_SECURE_NO_WARNINGS
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
using namespace GameLib;
#include "stage.h"
#include "common.h"
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
STAGE stage;
INITIAL_VALUE stage1=
{
	"DATA\\MAP\\test.txt",
	8,
	8,
	VECTOR2{64,64},
	VECTOR2{2,3},
};
void stage_init()
{
	stage.init(stage1);
}

void stage_update()
{

}

void stage_draw()
{
	stage.draw();
}

VECTOR2 Pstart(int stage_num)
{
	switch (stage_num)
	{
      case 0:
		  return stage.Pstart();
		break;
	}
	//return VECTOR2();
}

VECTOR2 Sstart(int stage_num)
{
	switch (stage_num)
	{
	case 0:
		return stage.Sstart();
		break;
	}
	//return VECTOR2();
}
VECTOR2 Send(int stage_num)
{
	switch (stage_num)
	{
	case 0:
		return stage.Send();
		break;
	}
	//return VECTOR2();
}