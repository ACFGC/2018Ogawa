#ifndef CTRAMPOLINE_H
#define CTRAMPOLINE_H

#include "CCharacter.h"

/*
�v���C���[�N���X
*/
class CTrampoline : public CCharacter {
public:

	//���R���C�_�ǉ�
	CSphereCollider mColSphere;

	static CTrampoline *spInstance; //�C���X�^���X�̃|�C���^

	CTrampoline(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
		//�e�̃N���X��������
		: CCharacter(x, y, z, w, h, d, rx, ry, rz)
	{
		//���R���C�_�̐ݒ�
		//���̃^�X�N��ݒ�
		mColSphere.mpTask = this;
		//�����s��̐ݒ�
		mColSphere.mpMatrix = &mBox.mMatrix;
		//���̔��a�̒����ݒ�
		mColSphere.mRadius = w;

		spInstance = this;
	}
	//�X�V����
	void Update();
	//�Փˏ���
	void OnCollision(C3DCollider *i, C3DCollider *y);
};

#endif