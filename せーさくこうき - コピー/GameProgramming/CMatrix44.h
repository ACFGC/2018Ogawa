#ifndef CMATRIX44_H
#define CMATRIX44_H

#include "CVector3.h"

class CMatrix44 {
public:
	//4x4��2�����z��
	float m[4][4];
	union //���p�� ���ʂ̗̈���Q�Ƃ���
	{
		float	f[16];
		float	m[4][4];
		struct
		{
			float	m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33;
		};
	};
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
	
	void SetQuaternion(float x, float y, float z, float w);
	const CMatrix44 operator * (float f) const;
	const CMatrix44 operator + (const CMatrix44 &r) const;
	void CMatrix44::operator += (const CMatrix44 &r);
	CMatrix44 CMatrix44::Transpose() const;

};

#endif
