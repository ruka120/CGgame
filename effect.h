#pragma once
//�G�t�F�N�g�֘A

enum//�G�t�F�N�g�ԍ�
{
	karioki=0,
	Effect_Max
};
namespace EFFECT
{ 
	//�G�t�F�N�g�Ăяo���֐�
	//int num -> �G�t�F�N�g�ԍ�
	//float posx,float posy ���� VECTER2  ->�\��������W(x,y)
	void set(int num, float posx, float posy);
	void set(int num, VECTOR2 pos);
	//�G�t�F�N�g�̈ꎞ��~�t���O�ݒ�֐�
	//���� bool�@isFlg(true->stop false->play)
	void pause(bool isFlg);
}