#pragma once
#include "add_on.h"
class PLAYER :public OBJ
{
public:
	int move_flg;//移動フラグ
	int life;//行動回数
	//移動フラグ
	//int XorY -> ｘ方向に動くかｙ方向に動くか(x->0,y->1)
	//float distance -> 移動距離
	//int time -> 何フレームかけて移動するか
	void move(float distance, int time);
};
void player_init();
void player_update();
void player_draw();
