#if(true)//おまけ
#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "counter.h"
using namespace GameLib;
extern Sprite* sprData[Spr_Max];
class COUNTER
{
private:
	int count;
	bool isUse=false;//使用しているかのフラグ
public:
	bool init(int count);
	void draw(int sc, float xpos, float ypos,float scale,int keta);
};
bool COUNTER::init(int count)
{
	if(!isUse)//使っていたら設定
	{
		isUse = true;
		this->count = count;
		return true;
	}
		return false;
}
void COUNTER::draw(int sc, float xpos, float ypos, float scale, int keta)
{
	while (keta--)
	{
		int num = sc % 10;
		float texPosX = num % 5 * (float)NUMBER_WIDTH;
		float texPosY = num / 5 * (float)NUMBER_HEIGHT;
		sprite_render(sprData[Number], xpos, ypos, scale, scale,
			texPosX, texPosY,
			NUMBER_WIDTH, NUMBER_HEIGHT,
			0, 0,
			0, 1, 1, 1);
		xpos -= NUMBER_WIDTH * scale;
		sc /= 10;
	}
}
#endif