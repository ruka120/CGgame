#pragma once
//エフェクト関連

enum//エフェクト番号
{
	karioki=0,
	Effect_Max
};
namespace EFFECT
{ 
	//エフェクト呼び出し関数
	//int num -> エフェクト番号
	//float posx,float posy 又は VECTER2  ->表示する座標(x,y)
	void set(int num, float posx, float posy);
	void set(int num, VECTOR2 pos);
	//エフェクトの一時停止フラグ設定関数
	//引数 bool　isFlg(true->stop false->play)
	void pause(bool isFlg);
}