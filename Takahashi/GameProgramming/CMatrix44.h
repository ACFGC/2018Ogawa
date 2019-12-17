#ifndef CMATRIX44_H
#define CMATRIX44_H

#include "CVector3.h"

class CMatrix44 {
public:
	//4x4��2�����z��
	float m[4][4];
	//�R���X�g���N�^
	CMatrix44() {
		Identity();
	}
	//�P�ʍs��ɐݒ�
	void Identity();
	//Y���𒆐S�ɉ�]
	void SetRotationY(float degree);
	//X���𒆐S�ɉ�]
	void SetRotationX(float degree);
	//�s��̕\��
	void Print();
	//*CVector3�̃I�[�o�[���[�h
	const CVector3 operator*(const CVector3 &v) const;
	//�ړ��s���ݒ�
	void SetTranslate(const CVector3 &v);
	//*CMatrix44�̃I�[�o�[���[�h
	const CMatrix44 operator*(const CMatrix44 &m) const;
};

#endif
