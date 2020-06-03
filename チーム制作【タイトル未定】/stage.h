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
	VECTOR2 Pstart();
	VECTOR2 Sstart();
	VECTOR2 Send();
	void draw();
};
//ギミックなど
class GIMIMICK  
{

};
void stage_init();
void stage_update();
void stage_draw();
VECTOR2 Pstart(int stage_num);
VECTOR2 Sstart(int stage_num);
VECTOR2 Send(int stage_num);


