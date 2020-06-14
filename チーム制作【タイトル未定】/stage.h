#pragma once
/********************************************************************/
/***************************ステージ*********************************/
/********************************************************************/
#include "add_on.h"
//チップ番号
struct CHIP_NUM
{
	int x;
	int y;
};


//初期値
struct INITIAL_VALUE
{
	char* fname;        // ファイルの名前
	int useX;           // 使うチップの横の数
	int useY;           // 使うチップの縦の数
	VECTOR2 scl;        // スケール
	VECTOR2 size;       // チップの大きさ
	CHIP_NUM Pstart;    // 開始時のプレイヤーの立ち位置
};
enum NEEDLE_STATE
{
	After_Out=0,  // 出た後
	On_the_way_In,// 入っている途中
	After_In,     // 入った後
	On_the_way_Out// 出ている途中
};
enum STAGE_TYPE
{
	Ground1 = 0,// 地面
	Ground2,    // 地面
	Ground3,	// 地面
	Ground4,	// 地面
	Ground5,	// 地面
	Wall_U,     // 壁(下)
	Wall_S,     // 壁(横)
	Wall_LT,    // 壁(左上)
	Wall_T,     // 壁(上）
	Wall_RT,    // 壁(右上）
	Needle,     // 棘 アニメーションする
	
};
//マップチップ用クラス
class MAP_CHIP:public OBJ
{
public:
	int type;
};
class STAGE
{
private:
	static const int X = 5;//画像データの横の数(改行用)
	int useX;            //使うチップの横の数
	int useY;            //使うチップの縦の数
	VECTOR2 scl;         //スケール
	VECTOR2 size;        //チップの大きさ
	VECTOR2 start;       //ステージの開始位置
	CHIP_NUM Pspawn;     //プレイヤーの初期位置
	MAP_CHIP data[32][32];    //ステージデータ格納場所
public:
	void init(INITIAL_VALUE);
	void draw();
	void data_translate(CHIP_NUM now_chip, int after);
	CHIP_NUM get_nowCnum(VECTOR2 pos);
	VECTOR2 get_pos(int numX, int numY);
	VECTOR2 get_size();
	int get_type(int numX, int numY);
	VECTOR2 Pstart();
	VECTOR2 Sstart();
	VECTOR2 Send();
};
void stage_init();
void stage_update();
void stage_draw();
void Sdata_translate(CHIP_NUM now_chip, int after);
CHIP_NUM get_nowCnum(VECTOR2 pos);
VECTOR2 Pstart();
VECTOR2 Sstart();
VECTOR2 Send();
VECTOR2 get_Cpos(int numX, int numY);
VECTOR2 get_Csize();
int get_Ctype(int numX, int numY);
/********************************************************************/
/***************************ギミック*********************************/
/********************************************************************/
#define GIMMICK_TEST (true)
struct GIMMICK_DATA
{
	int type;//ギミックの種類
	CHIP_NUM first;//マップチップ上での初期番号
};
enum GIMMICK_TYPE//0は使わない
{
	END = -1,//終了フラグ
	Gum = 1,
#if(GIMMICK_TEST)//テスト用
	White = 2,
	Bloac,
	Red,
	Green,
	Blue,

#endif
};

class GIMMICK
{
private:
	int type;
	VECTOR2 pos;
	VECTOR2 scl;
	VECTOR2 size;
	VECTOR2 center;
	bool exist;
public:
	bool hit(CHIP_NUM now_num);         //ギミックとの衝突判定関数
	int get_type()   { return type; }   //ギミックのタイプ取得関数
	bool get_exist() { return exist; }  //存在フラグ取得関数
	void destroy()   { exist = false; } //ギミック破壊関数
	void init(GIMMICK_DATA data);
	void update();
	void draw();
};

void gimmick_init();
void gimmick_update();
void gimmick_draw();
int G_hit(CHIP_NUM now_num);
void G_destroy(CHIP_NUM now_num);