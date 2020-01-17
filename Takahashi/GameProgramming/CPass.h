#ifndef CPASS_H
#define CPASS_H

#include "CCharacter.h"

/*
�v���C���[�N���X
*/
class CPass : public CCharacter {
public:
	//���R���C�_�ǉ�
	CSphereCollider mColSphere;

	static CPass *spInstance; //�C���X�^���X�̃|�C���^

	CPass(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
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

		mTaskTag = CCharacter::EGOAL;
	}
	//�X�V����
	void Update();
	//�Փˏ���
	void OnCollision(C3DCollider *i, C3DCollider *y);
};

#endif