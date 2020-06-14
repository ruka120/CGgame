#define	_CRT_SECURE_NO_WARNINGS
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
using namespace GameLib;
#include "common.h"

#include "stage.h"
/********************************************************************/
/***************************ステージ*********************************/
/********************************************************************/
void STAGE::init(INITIAL_VALUE value)
{
	//変数の初期化
	useX = value.useX;
	useY = value.useY;
	size = value.size;
	scl  = value.scl;
	Pspawn = value.Pstart;
	//開始位置の設定
	start = { ((SCREEN_WIDTH / 2) - (get_size().x*(useX / 2))),((SCREEN_HEIGHT / 2) - (get_size().y*(useY / 2))) };
	//ステージデータ
	FILE* fp;
	fp = fopen(value.fname, "r");
	if (!fp)return;
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			fscanf(fp, "%d,", &data[y][x].type);
			if (data[y][x].type == STAGE_TYPE::Needle)
			{
				data[y][x].set_state(NEEDLE_STATE::After_Out);
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);

}

VECTOR2 STAGE::get_pos(int numX, int numY)
{
	return VECTOR2{ start.x + (get_size().x*numX),start.y + (get_size().y*numY) };
}

VECTOR2 STAGE::get_size()
{
	return VECTOR2{size.x*scl.x,size.y*scl.y};
}

int STAGE::get_type(int numX, int numY)
{
	return data[numY][numX].type;
}

VECTOR2 STAGE::Pstart()
{
	VECTOR2 pos;
	pos = { (((SCREEN_WIDTH / 2) - (get_size().x*(useX / 2))) + (get_size().x*Pspawn.x)),(((SCREEN_HEIGHT / 2) - (get_size().y*(useY / 2))) + (get_size().y*Pspawn.y)) };
	return pos;
}

VECTOR2 STAGE::Sstart()
{
	return start;
}

VECTOR2 STAGE::Send()
{
	return VECTOR2{ start.x + (get_size().x*(useX - 1)),start.y + (get_size().y*(useY - 1)) };
}

void STAGE::draw()
{
	extern Sprite* sprData[Spr_Max];
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			switch (data[y][x].type)
			{
			default:
			sprite_render(sprData[Mapchip], start.x + (get_size().x*x), start.y + (get_size().y*y), scl.x, scl.y, size.x*(data[y][x].type % X), size.y*(data[y][x].type / X), size.x, size.y);
				break;
			case STAGE_TYPE::Needle:
				switch (data[y][x].get_state())
				{
				case NEEDLE_STATE::After_Out:
					//sprite_render
					break;
				case NEEDLE_STATE::On_the_way_In:
					//motion
					break;
				case NEEDLE_STATE::After_In:
					//sprite_render
					break;
				case NEEDLE_STATE::On_the_way_Out:
					//motion
					break;
				}
				break;
			}
		}
	}
}
void STAGE::data_translate(CHIP_NUM now_chip, int after)
{
	data[now_chip.y][now_chip.x].type = after;
}
CHIP_NUM STAGE::get_nowCnum(VECTOR2 pos)
{
	static Rect Crect;
	for (int y = 0; y < useY; y++)
	{
		for (int x = 0; x < useX; x++)
		{
			Crect = { (start.y + (get_size().y*y)),(start.y + (get_size().y*(y + 1))),(start.x + (get_size().x*x)),(start.x + (get_size().x*(x + 1))) };
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
    {2,2},
	{32,32},
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
//指定されたチップのタイプを変更する関数
void Sdata_translate(CHIP_NUM now_chip, int after)
{
	stage.data_translate(now_chip, after);
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
VECTOR2 get_Cpos(int numX, int numY)
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

#if GIMMICK_TEST
VECTOR4 color[]//ギミック用画像の代わり
{
	{1,1,1,1},//白
	{0,0,0,1},//黒
	{1,0,0,1},//赤
	{0,1,0,1},//緑
	{0,0,1,1},//青
};
GIMMICK_DATA test[]
= {
	{GIMMICK_TYPE::White,0,0},
	{GIMMICK_TYPE::Bloac,2,0},
	{GIMMICK_TYPE::Red  ,5,3},
	{GIMMICK_TYPE::Green,7,6},
	{GIMMICK_TYPE::Blue ,2,6},
	{-1,0,0}
};
#endif

void GIMMICK::init(GIMMICK_DATA data)
{
	type   = data.type;
	scl    = { 2,2 };
	size   = {32,32};
	pos    = stage.get_pos(data.first.x, data.first.y);
	center = pos + VECTOR2{ (size.x*scl.x)/2,(size.y*scl.y)/ 2 };
	exist  = true;
}

bool GIMMICK::hit(CHIP_NUM now_num)
{
	if (get_nowCnum(center).x == now_num.x&&get_nowCnum(center).y == now_num.y)
	{
		//switch (type)//各タイプごとの更新処理用の初期化
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
#if(GIMMICK_TEST)//テスト用
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
	primitive::rect(VECTOR2{ pos.x,pos.y }, VECTOR2{ size.x*scl.x,size.y*scl.y }, VECTOR2{ 0,0 }, 0, color[type - 2]);
#endif // _DEBUG

}

static const int gimmick_max = 8;//使えるギミックの最大数
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
	for (int i = 0; i < gimmick_max; i++)
	{
		if (!gimmick[i].get_exist()) continue;//存在していないならスキップ
		gimmick[i].update();
	}
}

void gimmick_draw()
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		if (!gimmick[i].get_exist()) continue;//存在していないならスキップ
		gimmick[i].draw();
	}
}



// ギミックと当たったかの判定
// CHIP_NUM now_num ->　現在のマップチップ上の番号
//　返り値　->　当たったギミックのタイプ又は０(何も当たっていない)
//現在のとか言ってるけど使い方は
//キー入力されたときの移動先のチップを入れて
//移動先で当たるかどうかを見る用の関数
int G_hit(CHIP_NUM now_num)
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		if (!gimmick[i].get_exist()) continue;//存在していないならスキップ
		if (gimmick[i].hit(now_num))return gimmick[i].get_type();
	}
	return 0;//何も当たっていない
}

void G_destroy(CHIP_NUM now_num)
{
	for (int i = 0; i < use_gimmick_num; i++)
	{
		if (!gimmick[i].get_exist()) continue;//存在していないならスキップ
		if (gimmick[i].hit(now_num))
		{
			gimmick[i].destroy();
		}
	}
}


