#ifndef C3DBOX_H
#define C3DBOX_H
//�O�p�`�N���X�̃C���N���[�h
#include "C3DTriangle.h"
/*
�����̃N���X
*/
class C3DBox {
public:
	//�F 0:�� 1:�� 2:�� 3:�A���t�@
	float mDiffuse[4];
	float w;	//��
	float h;	//����
	float d;	//���s��
	//�O�p�`12��
	C3DTriangle mTriangle[12];
	//��]�l
	CVector3 mRotation;
	//��]�s��
	CMatrix44 mMatrixRotation;
	//�ʒu
	CVector3 mPosition;
	//�ړ��s��
	CMatrix44 mMatrixTranslate;
	//�����s��
	CMatrix44 mMatrix;
	//�i�s����
	CVector3 mForward;
	//�i�s�̑���
	float mVelocity;
	C3DBox()
		: mVelocity(5.0f)
	{}
	//�����̂̐ݒ�
	void SetWHD(float w, float h, float d);
	//�����̂̕`��
	void Render();
	//�X�V����
	void Update();
	//�O�i����
	void Forward();
	//��]
	void LeftTurn();
	void RightTurn();
	//�g�U���̐ݒ�
	void SetDiffuse(float r, float g, float b, float a);
};

#endif
