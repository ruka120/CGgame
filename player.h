#pragma once
#include "add_on.h"
enum PLAYER_STATE
{
	GAME_OVER = -1,//GAME OVER
	Think = 0,     //思考
	Move,          //移動
	Bounce,        //跳ね返り
	Destroy,       //ブロック破壊
};
class PLAYER :public OBJ
{
private:
	CHIP_NUM chip_num;//現在のマップチップ上の番号
	int move_vector;  //移動方向
	int life;         //行動回数
	VECTOR2 distance; //移動距離
	VECTOR2 center;   //中心座標
	void reset();     //リセット関数
	void think();     //思考関数
	void move();      //移動関数
	void bounce();    //跳ね返り関数
	
#if (_DEBUG)
	void STATUS();
#endif
public:
	void init();
	void update();
	void draw();
};
void player_init();
void player_update();
void player_draw();
