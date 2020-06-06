#pragma once
/********************************************************************/
/***************************�X�e�[�W*********************************/
/********************************************************************/
//�`�b�v�ԍ�
struct CHIP_NUM
{
	int x;
	int y;
};


//�����l
struct INITIAL_VALUE
{
	char* fname;        //�t�@�C���̖��O
	int useX;           //�g���`�b�v�̉��̐�
	int useY;           //�g���`�b�v�̏c�̐�
	VECTOR2 size;       //�`�b�v�̑傫��
	CHIP_NUM Pstart;    //�J�n���̃v���C���[�̗����ʒu
};
enum STAGE_TYPE
{
	Ground=0,//�n��
	Wall,    //��
};

class STAGE
{
private:
	static const int X=5;//�摜�f�[�^�̉��̐�(���s�p)
	int useX;            //�g���`�b�v�̉��̐�
	int useY;            //�g���`�b�v�̏c�̐�
	VECTOR2 size;        //�`�b�v�̑傫��
	VECTOR2 start;       //�X�e�[�W�̊J�n�ʒu
	CHIP_NUM Pspawn;     //�v���C���[�̏����ʒu
	int data[32][32];    //�X�e�[�W�f�[�^�i�[�ꏊ
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
/***************************�M�~�b�N*********************************/
/********************************************************************/

struct GIMMICK_DATA
{
	int type;//�M�~�b�N�̎��
	CHIP_NUM first;//�}�b�v�`�b�v��ł̏����ԍ�
};
enum GIMMICK_TYPE
{
	END = -1,//�I���t���O
	
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
