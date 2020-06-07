////必要ヘッダーファイルのインクルード
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "effect.h"
using namespace GameLib;
extern Sprite* sprData[Spr_Max];
//エフェクト関連
bool isPause;
struct EFFECT_DATA//データ構造体
{
//初期化必要
	int time;             //切り替え時間
	int NumX;             //チップの横の個数
	int NumY;             //チップの縦の個数
	int max;              //チップの総数
	float sclx;           //スケール（X）
	float scly;           //スケール（Y）
	float dataposx;       //画像データの開始X座標
	float dataposy;       //画像データの開始Y座標
	float sizex;          //１チップの横の大きさ
	float sizey;          //１チップの縦の大きさ

};
struct DATA 
{
	EFFECT_DATA data;
};
EFFECT_DATA data1 =//エフェクト(1つ目)
{

};
DATA fx[Effect_Max]=
{
	data1
};
class FX //エフェクトクラス
{
private:
	int timer;
	VECTOR2 pos;
	int x;
	int y;
	int count;
	int data_num;//エフェクト番号
public:
	bool exist = false;//存在フラグ
	bool init(int effect_num, float posx, float posy)
	{
		if (exist)return true;//存在していたら終了
		//初期化
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
			//使っていたらスキップ
			if (effect[i].init(num, posx, posy))continue;
			break;
		}
	}
	void set(int num, VECTOR2 pos)
	{
		for (int i = 0; i < effect_max; i++)
		{
			//使っていたらスキップ
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
