#pragma once
/********************************************************************/
/***************************�X�e�[�W*********************************/
/********************************************************************/
#include "add_on.h"
//�`�b�v�ԍ�
struct CHIP_NUM
{
	int x;
	int y;
};


//�����l
struct INITIAL_VALUE
{
	char* fname;        // �t�@�C���̖��O
	int useX;           // �g���`�b�v�̉��̐�
	int useY;           // �g���`�b�v�̏c�̐�
	VECTOR2 scl;        // �X�P�[��
	VECTOR2 size;       // �`�b�v�̑傫��
	CHIP_NUM Pstart;    // �J�n���̃v���C���[�̗����ʒu
};
enum NEEDLE_STATE
{
	After_Out=0,  // �o����
	On_the_way_In,// �����Ă���r��
	After_In,     // ��������
	On_the_way_Out// �o�Ă���r��
};
enum STAGE_TYPE
{
	Ground1 = 0,// �n��
	Ground2,    // �n��
	Ground3,	// �n��
	Ground4,	// �n��
	Ground5,	// �n��
	Wall_U,     // ��(��)
	Wall_S,     // ��(��)
	Wall_LT,    // ��(����)
	Wall_T,     // ��(��j
	Wall_RT,    // ��(�E��j
	Needle,     // �� �A�j���[�V��������
	
};
//�}�b�v�`�b�v�p�N���X
class MAP_CHIP:public OBJ
{
public:
	int type;
};
class STAGE
{
private:
	static const int X = 5;//�摜�f�[�^�̉��̐�(���s�p)
	int useX;            //�g���`�b�v�̉��̐�
	int useY;            //�g���`�b�v�̏c�̐�
	VECTOR2 scl;         //�X�P�[��
	VECTOR2 size;        //�`�b�v�̑傫��
	VECTOR2 start;       //�X�e�[�W�̊J�n�ʒu
	CHIP_NUM Pspawn;     //�v���C���[�̏����ʒu
	MAP_CHIP data[32][32];    //�X�e�[�W�f�[�^�i�[�ꏊ
public:
	void init(INITIAL_VALUE);
	void draw();
	void data_translate(CHIP_NUM now_chip, int after);
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
void Sdata_translate(CHIP_NUM now_chip, int after);
CHIP_NUM get_nowCnum(VECTOR2 pos);
VECTOR2 Pstart();
VECTOR2 Sstart();
VECTOR2 Send();
VECTOR2 get_Cpos(int numX, int numY);
VECTOR2 get_Csize();
int get_Ctype(int numX, int numY);
/********************************************************************/
/***************************�M�~�b�N*********************************/
/********************************************************************/
#define GIMMICK_TEST (true)
struct GIMMICK_DATA
{
	int type;//�M�~�b�N�̎��
	CHIP_NUM first;//�}�b�v�`�b�v��ł̏����ԍ�
};
enum GIMMICK_TYPE//0�͎g��Ȃ�
{
	END = -1,//�I���t���O
	Gum = 1,
#if(GIMMICK_TEST)//�e�X�g�p
	White = 2,
	Bloac,
	Red,
	Green,
	Blue,

#endif
};

class GIMMICK
{
private:
	int type;
	VECTOR2 pos;
	VECTOR2 scl;
	VECTOR2 size;
	VECTOR2 center;
	bool exist;
public:
	bool hit(CHIP_NUM now_num);         //�M�~�b�N�Ƃ̏Փ˔���֐�
	int get_type()   { return type; }   //�M�~�b�N�̃^�C�v�擾�֐�
	bool get_exist() { return exist; }  //���݃t���O�擾�֐�
	void destroy()   { exist = false; } //�M�~�b�N�j��֐�
	void init(GIMMICK_DATA data);
	void update();
	void draw();
};

void gimmick_init();
void gimmick_update();
void gimmick_draw();
int G_hit(CHIP_NUM now_num);
void G_destroy(CHIP_NUM now_num);