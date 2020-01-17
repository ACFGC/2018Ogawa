#ifndef CVECTOR3_H
#define CVECTOR3_H

#define _USE_MATH_DEFINES	//���w���C�u������M_PI��L���ɂ���
#include <math.h>	//���w���C�u�����̃C���N���[�h
//?
class CMatrix44;
/*
 3D�x�N�g���N���X
*/
class CVector3 {
public:
	//3D���W
	float x;
	float y;
	float z;
	//�f�t�H���g�R���X�g���N�^
	CVector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}
	//�����t���R���X�g���N�^
	CVector3(float ix, float iy, float iz)
		: x(ix), y(iy), z(iz)
	{}

	//*float�̃I�[�o�[���[�h
	const CVector3 operator*(float f) const {
		return CVector3(x*f, y*f, z*f);
	}
	//+CVector3�̃I�[�o�[���[�h
	const CVector3 operator+(const CVector3 &v) const {
		return CVector3(x + v.x, y + v.y, z + v.z);
	}
	//-CVector3�̃I�[�o�[���[�h
	const CVector3 operator-(const CVector3 &v) const {
		return CVector3(x - v.x, y - v.y, z - v.z);
	}
	/*
	 ���������߂�
	*/
	float CVector3::Length() {
		return sqrtf(x*x + y*y + z*z);
	}
	/*
	 �x�N�g���l����x��y���̉�]�p�x�����߂�
	 atan2(y, x) -180���`180��
	*/
	CVector3 CVector3::GetRotation() {
		CVector3 rot;
		//Y���̉�]�p�x
		rot.y = -(atan2f(z, x)) * 180.0f / M_PI;
		//X���̉�]�p�x
//		rot.x = -(atan2f(y, Length())) * 180.0f / M_PI;
		rot.x = -(atan2f(y, sqrtf(x*x+z*z))) * 180.0f / M_PI;
		return rot;
	}
	/*
	 ���ς����߂�
	*/
	float CVector3::Dot(const CVector3 &v) {
		return x * v.x + y * v.y + z * v.z;
	}
	/* ���K�������x�N�g����Ԃ�
	�x�N�g���̐��K���F�傫����1�ɂ���
	*/
	CVector3 CVector3::normalize() {
		float len = Length();
		return CVector3(x / len, y / len, z / len);
	}
	//CMatrix44�Ƃ̊|���Z
	const CVector3 operator * (const CMatrix44 &m) const;

	void CVector3::operator += (const CVector3 &v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}

};


#endif
