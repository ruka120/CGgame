#pragma once
#include "add_on.h"


class PLAYER :public OBJ
{
private:
	CHIP_NUM chip_num;//現在のマップチップ上の番号
	int move_vector;//移動方向
	int life;//行動回数
	VECTOR2 distance;//移動距離
	VECTOR2 center;  //中心座標
	void move(float distance, int time);
	void reset();
public:
	void init();
	void update();
	void draw();
};
void player_init();
void player_update();
void player_draw();
