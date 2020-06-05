#pragma once

//�����l
struct INITIAL_VALUE
{
	char* fname;        //�t�@�C���̖��O
	int useX;           //�g���`�b�v�̉��̐�
	int useY;           //�g���`�b�v�̏c�̐�
	VECTOR2 size;       //�`�b�v�̑傫��
	VECTOR2 Pstart;     //�J�n���̃v���C���[�̗����ʒu
};
enum STAGE_TYPE
{

};
//�X�e�[�W
class STAGE
{
private:
	static const int X=5;//�摜�f�[�^�̉��̐�(���s�p)
	int useX;            //�g���`�b�v�̉��̐�
	int useY;            //�g���`�b�v�̏c�̐�
	VECTOR2 size;        //�`�b�v�̑傫��
	VECTOR2 start;       //�X�e�[�W�̊J�n�ʒu
	VECTOR2 Pspawn;      //�v���C���[�̏����ʒu
	int data[32][32];    //�X�e�[�W�f�[�^�i�[�ꏊ
public:
	void init(INITIAL_VALUE);
	VECTOR2 get_pos(int numX, int numY);
	VECTOR2 get_size();
	VECTOR2 Pstart();
	VECTOR2 Sstart();
	VECTOR2 Send();
	void draw();
};
void stage_init();
void stage_update();
void stage_draw();
VECTOR2 Pstart();
VECTOR2 Sstart();
VECTOR2 Send();
VECTOR2 get_pos(int numX,int numY);
VECTOR2 get_size();
//�M�~�b�N�Ȃ�
struct GIMMICK_DATA
{
	int type;//�M�~�b�N�̎��
	int numX;//�}�b�v�`�b�v��̏����ԍ�(X)
	int numY;//�}�b�v�`�b�v��̏����ԍ�(Y)
};
enum GIMMICK_TYPE
{
	END = -1,//�I���t���O
	
};
class GIMMICK  
{
public:
	int type;
	VECTOR2 pos;
	void init(GIMMICK_DATA data);
	void draw();
};
void gimmick_init();
void gimmick_update();
void gimmick_draw();
