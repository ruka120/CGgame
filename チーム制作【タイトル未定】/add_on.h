#pragma once

//構造体
//struct Rect
//{
//	float top;
//	float under;
//	float left;
//	float right;
//};

//クラス
class Chip
{
public:
	int x;
	int y;
	int count;
	void reset();
};
//OBJ基底クラス
class OBJ
{
private:
protected:
#if(true)//ステータス関連
	int state;
#endif//ステータス関連
#if (true)//アニメーション関連
	//前フレームの状態遷移の保存先
	int Previous_state;
	//アニメーション情報関連
	int animetimer;
	Chip chip[2];
	bool timer_init(int STATE);
	//int switching_time;
	//一時停止フラグ true->stop false->play
	bool isPause;
public:
	//アニメ・モーションの一時停止フラグ設定関数
	//引数 bool　isFlg(true->stop false->play)
	void pause(bool isFlg);
#endif//アニメーション関連

public:
	OBJ();
#if(true)//ステータス関連
	Rect rect;
	void set_state(int STATE);
	int get_state();
	VECTOR2 pos;
	bool exist;
#endif//ステータス関連
#if(true)
	virtual void init() {};
	virtual void update() {};
	virtual void draw() {};
#endif
#if(true)//アニメーション関連
    //画像データ
    //切り替え時間(フレーム単位)
    //横、縦のチップの個数(x,y)
    //チップの総数
    //描写位置(x,y)
    //スケール(x,y)
    //画像の開始位置(x,y)
    //1チップの大きさ(x,y)
    //基準点(x,y)
    //角度(ラジアン)
    //色(r,g,b,a)
	void anim(GameLib::Sprite* data,
		const int time,
		int NumX, int NumY,
		int max,
		float posx, float posy,
		float sclx, float scly,
		float dataposx, float dataposy,
		float sizex, float sizey,
		float StandardX = 0.0f, float StandardY = 0.0f,
		float rad = 0.0f,
		float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
	//画像データ
    //モーション終了後の状態
    //切り替え時間(フレーム単位)
    //横、縦のチップの個数(x,y)
    //チップの総数
    //描写位置(x,y)
    //スケール(x,y)
    //画像の開始位置(x,y)
    //1チップの大きさ(x,y)
    //基準点(x,y)
    //角度(ラジアン)
    //色(r,g,b,a)
	void motion(GameLib::Sprite* data,
		int after,
		const int time,
		int NumX, int NumY,
		int max,
		float posx, float posy,
		float sclx, float scly,
		float dataposx, float dataposy,
		float sizex, float sizey,
		float StandardX = 0.0f, float StandardY = 0.0f,
		float rad = 0.0f,
		float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
#endif//アニメーション関連
};




/////当たり判定/////
static class JUDGE
{
public:


	//当たり判定代入用の変数
	//矩形の当たり判定
	//float px_a,float py_a ->当たり判定を行う2つのオブジェクトの1つ目の左上の座標(X,Y)
	//int sx_a,int sy_a ->当たり判定を行う2つのオブジェクトの1つ目の横と縦の長さ(X,Y)
	//float px_a,float py_a ->当たり判定を行う2つのオブジェクトの2つ目の左上の座標(X,Y)
	//int sx_a,int sy_a ->当たり判定を行う2つのオブジェクトの2つ目の横と縦の長さ(X,Y)
	bool rect(float px_a, float py_a, int sx_a, int sy_a,
		float px_b, float py_b, int sx_b, int sy_b);
	bool rect(Rect a, Rect b);
	////矩形の当たり判定
	//当たり判定を行う矩形の四点の座標(top,under,left,right)又はRECT構造体
	//当たり判定を行う座標(x,y)又はVECTOR2(pos)
	bool rect(float top, float under, float left, float right, float posx, float posy);
	bool rect(float top, float under, float left, float right, VECTOR2 pos);
	bool rect(Rect rect, VECTOR2 pos);
	bool rect(Rect rect, float posx, float posy);

	//円の当たり判定
	//float px_a,folat py_a->当たり判定を行う2つのオブジェクトの1つ目の中心座標(X,Y)又はVECTOR2(pos)
	//int r_a-> 当たり判定を行う2つのオブジェクトの1つ目の半径
	//float px_b,folat py_b->当たり判定を行う2つのオブジェクトの2つ目の中心座標(X,Y)又はVECTOR2(pos)
	//int r_b-> 当たり判定を行う2つのオブジェクトの2つ目の半径
	bool circle(float px_a, float py_a, int r_a, float px_b, float py_b, int r_b);
	bool circle(VECTOR2 posa, int r_a, VECTOR2 posb, int r_b);
	bool circle(VECTOR2 posa, int r_a, float px_b, float py_b, int r_b);
	bool circle(float px_a, float py_a, int r_a, VECTOR2 posb, int r_b);

	//レーザーとの当たり判定
	//int xory ->ｘ座標の判定かｙ座標の判定の設定　(0->x,1->y)
	//float biginpos, float finfin ->判定の初め(bigin)と終わり(fin)の座標
	//float judgepos, float laserwidth ->判定線(レーザーの中心線)と幅(判定線からレーザーの)
	bool laser(int xory, float biginpos, float finpos,
		        float judgepos, float laserwidth,
		        VECTOR2 pos, float objwidth);
}Judge;
