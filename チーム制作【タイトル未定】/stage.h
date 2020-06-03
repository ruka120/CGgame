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
	VECTOR2 Pstart();
	VECTOR2 Sstart();
	VECTOR2 Send();
	void draw();
};
//�M�~�b�N�Ȃ�
class GIMIMICK  
{

};
void stage_init();
void stage_update();
void stage_draw();
VECTOR2 Pstart(int stage_num);
VECTOR2 Sstart(int stage_num);
VECTOR2 Send(int stage_num);


