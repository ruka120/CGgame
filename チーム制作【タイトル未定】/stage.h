#pragma once
/********************************************************************/
/***************************ステージ*********************************/
/********************************************************************/
//チップ番号
struct CHIP_NUM
{
	int x;
	int y;
};


//初期値
struct INITIAL_VALUE
{
	char* fname;        //ファイルの名前
	int useX;           //使うチップの横の数
	int useY;           //使うチップの縦の数
	VECTOR2 size;       //チップの大きさ
	CHIP_NUM Pstart;    //開始時のプレイヤーの立ち位置
};
enum STAGE_TYPE
{
	Ground=0,//地面
	Wall,    //壁
};

class STAGE
{
private:
	static const int X=5;//画像データの横の数(改行用)
	int useX;            //使うチップの横の数
	int useY;            //使うチップの縦の数
	VECTOR2 size;        //チップの大きさ
	VECTOR2 start;       //ステージの開始位置
	CHIP_NUM Pspawn;     //プレイヤーの初期位置
	int data[32][32];    //ステージデータ格納場所
public:
	void init(INITIAL_VALUE);
	void draw();
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
CHIP_NUM get_nowCnum(VECTOR2 pos);
VECTOR2 Pstart();
VECTOR2 Sstart();
VECTOR2 Send();
VECTOR2 get_Cpos(int numX,int numY);
VECTOR2 get_Csize();
int get_Ctype(int numX, int numY);
/********************************************************************/
/***************************ギミック*********************************/
/********************************************************************/

struct GIMMICK_DATA
{
	int type;//ギミックの種類
	CHIP_NUM first;//マップチップ上での初期番号
};
enum GIMMICK_TYPE
{
	END = -1,//終了フラグ
	
};

class GIMMICK  
{
	int type;
	VECTOR2 pos;
public:
	void init(GIMMICK_DATA data);
	void draw();
};

void gimmick_init();
void gimmick_update();
void gimmick_draw();
