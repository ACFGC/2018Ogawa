#include "CMatrix33.h"
#include <stdio.h>	//printf�̃C���N���[�h
#define _USE_MATH_DEFINES	//���w���C�u������M_PI��L���ɂ���
#include <math.h>	//���w���C�u�����̃C���N���[�h
/*
 Identity()
 �P�ʍs����쐬����
*/
void CMatrix33::Identity() {
	//2�����z��m�S�̂�0�N���A
	memset(m, 0, sizeof(m));
	//�΂߉��̑Ίp�����1�ݒ�
	m[0][0] = m[1][1] = m[2][2] = 1.0f;
}
/*
m[0][0] m[0][1] m[0][2]
m[1][0] m[1][1] m[1][2]
m[2][0] m[2][1] m[2][2]
�̐ݒ�l���R���\�[���o�͂���
*/
void CMatrix33::Print() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//m[i][j]�̒l���o�͂���
			//%f float�^�̒l�ɒu��������
			printf("%f ", m[i][j]);
		}
		//���s���� \n ���s
		printf("\n");
	}
}

//��]�s��̐ݒ�
void CMatrix33::SetRotation(float degree) {
	//�x���烉�W�A���ɕϊ�����
	float radian = degree * M_PI / 180.0f;
	//�T�C�������߂�
	float sin = sinf(radian);
	//�R�T�C�������߂�
	float cos = cosf(radian);
	//�P�ʍs��ɂ���
	Identity();
	//��]�l�̐ݒ�
	m[0][0] = m[1][1] = cos;
	m[0][1] = -sin;
	m[1][0] = sin;
}
//2�����x�N�g���N���X���|����
const CVector2 CMatrix33::MultiVector2(const CVector2 &v) const {
	CVector2 vector;
	vector.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2];
	vector.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2];
	return vector;
}
// *���Z�q�̃I�[�o�[���[�h
const CVector2 CMatrix33::operator*(const CVector2 &v) const {
	return MultiVector2(v);
}

//�ړ��s��̐ݒ�
void CMatrix33::SetTranslate(float x, float y) {
	//�P�ʍs��ɐݒ�
	Identity();
	//�ړ��ʐݒ�
	m[0][2] = x;
	m[1][2] = y;
}
//3�s3��s��N���X���|����
const CMatrix33 CMatrix33::MultiMatrix33(const CMatrix33 &a) const {
	CMatrix33 r;
	r.m[0][0] = m[0][0] * a.m[0][0] + m[0][1] * a.m[1][0] + m[0][2] * a.m[2][0];
	r.m[0][1] = m[0][0] * a.m[0][1] + m[0][1] * a.m[1][1] + m[0][2] * a.m[2][1];
	r.m[0][2] = m[0][0] * a.m[0][2] + m[0][1] * a.m[1][2] + m[0][2] * a.m[2][2];

	r.m[1][0] = m[1][0] * a.m[0][0] + m[1][1] * a.m[1][0] + m[1][2] * a.m[2][0];
	r.m[1][1] = m[1][0] * a.m[0][1] + m[1][1] * a.m[1][1] + m[1][2] * a.m[2][1];
	r.m[1][2] = m[1][0] * a.m[0][2] + m[1][1] * a.m[1][2] + m[1][2] * a.m[2][2];

	r.m[2][0] = m[2][0] * a.m[0][0] + m[2][1] * a.m[1][0] + m[2][2] * a.m[2][0];
	r.m[2][1] = m[2][0] * a.m[0][1] + m[2][1] * a.m[1][1] + m[2][2] * a.m[2][1];
	r.m[2][2] = m[2][0] * a.m[0][2] + m[2][1] * a.m[1][2] + m[2][2] * a.m[2][2];

	return r;
}

// *���Z�q�̃I�[�o�[���[�h
const CMatrix33 CMatrix33::operator*(const CMatrix33 &a) const {
	return MultiMatrix33(a);
}

//�g��k���s��̐ݒ�
void CMatrix33::SetScale(float x, float y) {
	//�P�ʍs��ɐݒ�
	Identity();
	m[0][0] = x;
	m[1][1] = y;
}
