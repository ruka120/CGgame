#include "./GameLib/game_lib.h"
#include "./GameLib/template.h"
#include "./GameLib/input_manager.h"
#include "./GameLib/obj2d_data.h"
#include "common.h"
#include "stage.h"
#include "player.h"

using namespace GameLib;
using namespace input;

enum MOVE_VECTOR//�ړ�����
{
	Stop = 0,
	Right,
	Left,
	Up,
	Down,
};


namespace STATG
{
	VECTOR2 end;
	VECTOR2 start;
};
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

void PLAYER::reset()
{
	gimmick_init();
	state = PLAYER_STATE::Think;
	pos = Pstart();
	life = 16;
	center = { pos.x + ((size.x*scl.x) / 2),pos.y + ((size.y*scl.y) / 2) };
	chip_num = get_nowCnum(center);
	move_vector = MOVE_VECTOR::Stop;
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

void PLAYER::think()
{
	if (move_vector != MOVE_VECTOR::Stop)move_vector = MOVE_VECTOR::Stop;
	//�ړ�
	if (life>0)
	{
		if (RIGHT&&get_Ctype(chip_num.x + 1, chip_num.y) != STAGE_TYPE::Wall_S)
		{
			move_vector = MOVE_VECTOR::Right;
			//�M�~�b�N�Ƃ̔���
			switch (G_hit(CHIP_NUM{ chip_num.x + 1, chip_num.y }))
			{
			default:
				break;
			case 0:
				state = PLAYER_STATE::Move;
				break;
#if(GIMMICK_TEST)
			case GIMMICK_TYPE::Red:
				state = PLAYER_STATE::Bounce;
				break;
			case GIMMICK_TYPE::Blue:
				state = PLAYER_STATE::Destroy;
				G_destroy(CHIP_NUM{ chip_num.x + 1, chip_num.y });
				break;
#endif
			}
		}
		if (LEFT &&get_Ctype(chip_num.x - 1, chip_num.y) != STAGE_TYPE::Wall_S)
		{
			move_vector = MOVE_VECTOR::Left;
			//�M�~�b�N�Ƃ̔���
			switch (G_hit(CHIP_NUM{ chip_num.x - 1, chip_num.y }))
			{
			default:
				break;
			case 0:
				state = PLAYER_STATE::Move;
				break;
#if(GIMMICK_TEST)
			case GIMMICK_TYPE::Red:
				state = PLAYER_STATE::Bounce;
				break;
			case GIMMICK_TYPE::Blue:
				state = PLAYER_STATE::Destroy;
				G_destroy(CHIP_NUM{ chip_num.x - 1, chip_num.y });
				break;
#endif
			}
		}
		if (UP   &&get_Ctype(chip_num.x, chip_num.y - 1) != STAGE_TYPE::Wall_T)
		{
			move_vector = MOVE_VECTOR::Up;
			//�M�~�b�N�Ƃ̔���
			switch (G_hit(CHIP_NUM{ chip_num.x, chip_num.y - 1 }))
			{
			default:
				break;
			case 0:
				state = PLAYER_STATE::Move;
				break;
#if(GIMMICK_TEST)
			case GIMMICK_TYPE::Red:
				state = PLAYER_STATE::Bounce;
				break;
			case GIMMICK_TYPE::Blue:
				state = PLAYER_STATE::Destroy;
				G_destroy(CHIP_NUM{ chip_num.x, chip_num.y-1 });
				break;
#endif
			}
		}
		if (DOWN &&get_Ctype(chip_num.x, chip_num.y + 1) != STAGE_TYPE::Wall_U)
		{
			move_vector = MOVE_VECTOR::Down;
			//�M�~�b�N�Ƃ̔���
			switch (G_hit(CHIP_NUM{ chip_num.x, chip_num.y + 1 }))
			{
			default:
				break;
			case 0:
				state = PLAYER_STATE::Move;
				break;
#if(GIMMICK_TEST)
			case GIMMICK_TYPE::Red:
				state = PLAYER_STATE::Bounce;
				break;
			case GIMMICK_TYPE::Blue:
				state = PLAYER_STATE::Destroy;
				G_destroy(CHIP_NUM{ chip_num.x, chip_num.y + 1 });
				break;
#endif
			}
		}

	}
	else if (RIGHT | LEFT | UP | DOWN)
	{
		state = PLAYER_STATE::GAME_OVER;
	}
}
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

//�ړ�
void PLAYER::move()
{
	static const int PMOVE_TIME = 30;//�ړ�����
	static int count = 0;//�o�ߎ���
	switch (move_vector)
	{
	default://�ړ������ȊO�������Ă�����I��
		state = PLAYER_STATE::Think;
		life--;
		chip_num = get_nowCnum(center);
		count = 0;
		return;
	case MOVE_VECTOR::Left:
		pos.x -= (distance.x / PMOVE_TIME);
		count++;
		break;
	case MOVE_VECTOR::Right:
		pos.x += (distance.x / PMOVE_TIME);
		count++;
		break;
	case MOVE_VECTOR::Up:
		pos.y -= (distance.y / PMOVE_TIME);
		count++;
		break;
	case MOVE_VECTOR::Down:
		pos.y += (distance.y / PMOVE_TIME);
		count++;
		break;
	}
	if (count >= PMOVE_TIME)
	{
		state = PLAYER_STATE::Think;
		life--;
		chip_num = get_nowCnum(center);
		count = 0;
	}
}

void PLAYER::bounce()
{
	static int count = 0;//�o�ߎ���
	static int Bstate = 0;//���˕Ԃ�̏��
	//�ړ����Ԃ�<<����>> ���@�d�v
	//(�ړ����Ԃ̔����Œ��˕Ԃ��Ԃ�؂�ւ���̂Ō��̏ꏊ�ɖ߂��悤�Ɉړ����Ԃ̂������ɕK���Ȃ�悤�ɂ��邽��)
	static const int PMOVE_HALFTIME = 10;
	switch (Bstate)
	{
	case 0:
		switch (move_vector)
		{
		default://�ړ������ȊO�������Ă�����I��
			state = PLAYER_STATE::Think;
			return;
		case MOVE_VECTOR::Left:
			pos.x -= (distance.x / (PMOVE_HALFTIME * 2));
			count++;
			break;
		case MOVE_VECTOR::Right:
			pos.x += (distance.x / (PMOVE_HALFTIME * 2));
			count++;
			break;
		case MOVE_VECTOR::Up:
			pos.y -= (distance.y / (PMOVE_HALFTIME * 2));
			count++;
			break;
		case MOVE_VECTOR::Down:
			pos.y += (distance.y / (PMOVE_HALFTIME * 2));
			count++;
			break;
		}
		if (count >=PMOVE_HALFTIME)
			Bstate++;
		break;
	case 1:
		switch (move_vector)
		{
		default://�ړ������ȊO�������Ă�����I��
			state = PLAYER_STATE::Think;
			return;
		case MOVE_VECTOR::Left:
			pos.x += (distance.x / (PMOVE_HALFTIME * 2));
			count++;
			break;
		case MOVE_VECTOR::Right:
			pos.x -= (distance.x / (PMOVE_HALFTIME * 2));
			count++;
			break;
		case MOVE_VECTOR::Up:
			pos.y += (distance.y / (PMOVE_HALFTIME * 2));
			count++;
			break;
		case MOVE_VECTOR::Down:
			pos.y -= (distance.y / (PMOVE_HALFTIME * 2));
			count++;
			break;
		}
		if (count >= (PMOVE_HALFTIME*2))
		{
			state = PLAYER_STATE::Think;
			life--;
			chip_num = get_nowCnum(center);
			Bstate = 0;
			count = 0;
		}
		break;
	default://�ړ������ȊO�������Ă�����I��
		state = PLAYER_STATE::Think;
		life--;
		chip_num = get_nowCnum(center);
		Bstate = 0;
		count = 0;
		return;
	}
}
	/**********************************************************************************************/
	/**********************************************************************************************/
	/**********************************************************************************************/

#if (_DEBUG)//���Ȃ��Ă�OK
	void PLAYER::STATUS()
	{
		debug::setString("///// STATUS /////");
		debug::setString(" LIFE  [%d]", life);
		debug::setString(" STATE  [%d]", state);
		debug::setString(" POS  [%d][%d] = TYPE [%d]", chip_num.x, chip_num.y,get_Ctype(chip_num.x, chip_num.y));
		if (STATE(0)&PAD_RIGHT) { debug::setString("THE KEY BEING PRESSED [RIGHT]"); }
		else debug::setString("");
		if (STATE(0)&PAD_LEFT) { debug::setString("THE KEY BEING PRESSED [LEFT]"); }
		else debug::setString("");
		if (STATE(0)&PAD_UP) { debug::setString("THE KEY BEING PRESSED [UP]"); }
		else debug::setString("");
		if (STATE(0)&PAD_DOWN) { debug::setString("THE KEY BEING PRESSED [DOWN]"); }
		else debug::setString("");
		debug::setString(" GIMMICK HIT FLG");
		debug::setString(" [0] ->NOT HIT [OTHER THAN THAT] ->FALSE");
		debug::setString(" RIGHT [%d]", G_hit(CHIP_NUM{ chip_num.x + 1, chip_num.y }));
		debug::setString(" LEFT  [%d]", G_hit(CHIP_NUM{ chip_num.x - 1, chip_num.y }));
		debug::setString(" UP    [%d]", G_hit(CHIP_NUM{ chip_num.x, chip_num.y - 1 }));
		debug::setString(" DOWN  [%d]", G_hit(CHIP_NUM{ chip_num.x, chip_num.y + 1 }));
		if (state == PLAYER_STATE::GAME_OVER)
		{
			debug::setString("////////////////////////");
			debug::setString("/////  GAME  OVER  /////");
			debug::setString("////////////////////////");
		}
		else
		{
			debug::setString("");
			debug::setString("");
			debug::setString("");
		}
	}

#endif
/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/
void PLAYER::init()
{
	state = PLAYER_STATE::Think;
	pos = Pstart();
	STATG::start = Sstart();
	STATG::end = Send();
	life = 16;
	distance = get_Csize();
	scl = { 1,1 };
	size = {64,64};//���ۂ̃T�C�Y
	center = { pos.x + ((size.x*scl.x) / 2),pos.y + ((size.y*scl.y )/ 2) };
	chip_num = get_nowCnum(center);
	move_vector = MOVE_VECTOR::Stop;

}
void PLAYER::update()
{

	center = { pos.x + ((size.x*scl.x) / 2),pos.y + ((size.y*scl.y) / 2) };
	switch (state)
	{
	default:
		break;
	case PLAYER_STATE::Think:
		think();
		break;
	case PLAYER_STATE::Move:
		move();	
		break;
	case PLAYER_STATE::Bounce:
		bounce();
		break;
	case PLAYER_STATE::Destroy://(�������͈ړ��Ɠ���)
		move();
		break;
	}
#if (_DEBUG)//[�f�o�b�O�p]�X�e�[�^�X�\��
	STATUS();
#endif
#if (_DEBUG)//�f�o�b�O�p�����{�^��
//�ړ��񐔂̃��Z�b�g
	if (TRG(0)&PAD_F1) { reset(); }
#endif // (_DEBUG)

	
	//�ړ�����
	if (pos.x < STATG::start.x) pos.x = STATG::start.x;
	if (pos.x > STATG::end.x)   pos.x = STATG::end.x;
	if (pos.y < STATG::start.y) pos.y = STATG::start.y;
	if (pos.y > STATG::end.y)   pos.y = STATG::end.y;
}

void PLAYER::draw()
{
#if(_DEBUG)
	debug::display(1.0f,1.0f,1.0f,0.8f,0.8f);
#endif
	primitive::rect(pos.x, pos.y, size.x, size.y, 0, 0, 0, 1, 1, 1, 0.8);
}

/**********************************************************************************************/
/**********************************************************************************************/
/**********************************************************************************************/

PLAYER player;
void player_init()
{
	player.init();
}

void player_update()
{
	player.update();
}

void player_draw()
{
	player.draw();
}
