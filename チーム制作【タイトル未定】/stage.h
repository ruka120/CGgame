#pragma once

//初期値
struct INITIAL_VALUE
{
	char* fname;        //ファイルの名前
	int useX;           //使うチップの横の数
	int useY;           //使うチップの縦の数
	VECTOR2 size;       //チップの大きさ
	VECTOR2 Pstart;     //開始時のプレイヤーの立ち位置
};
enum STAGE_TYPE
{

};
//ステージ
class STAGE
{
private:
	static const int X=5;//画像データの横の数(改行用)
	int useX;            //使うチップの横の数
	int useY;            //使うチップの縦の数
	VECTOR2 size;        //チップの大きさ
	VECTOR2 start;       //ステージの開始位置
	VECTOR2 Pspawn;      //プレイヤーの初期位置
	int data[32][32];    //ステージデータ格納場所
public:
	void init(INITIAL_VALUE);
	VECTOR2 get_pos(int numX, int numY);
	VECTOR2 get_size();
	VECTOR2 Pstart();
	VECTOR2 Sstart();
	VECTOR2 Send();
	void draw();
};
void stage_init();
void stage_update();
void stage_draw();
VECTOR2 Pstart();
VECTOR2 Sstart();
VECTOR2 Send();
VECTOR2 get_pos(int numX,int numY);
VECTOR2 get_size();
//ギミックなど
struct GIMMICK_DATA
{
	int type;//ギミックの種類
	int numX;//マップチップ上の初期番号(X)
	int numY;//マップチップ上の初期番号(Y)
};
enum GIMMICK_TYPE
{
	END = -1,//終了フラグ
	
};
class GIMMICK  
{
public:
	int type;
	VECTOR2 pos;
	void init(GIMMICK_DATA data);
	void draw();
};
void gimmick_init();
void gimmick_update();
void gimmick_draw();
