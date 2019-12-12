#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
#include "CBall.h"
/*
�v���C���[�N���X
*/
class CPlayer : public CCharacter {
public:
	//���R���C�_�ǉ�
	CSphereCollider mColSphere;
	//�ړ����x
	CVector3 mVelocity;

	int Jump = 0; //�W�����v��
	int Goal = 1; //�S�[������ 1�N���A�@2���s
	int Happy = 0; //�n�b�s�[���
	int Time = 0 * 60; //�^�C��

	int x = 0;
	int z = 0;//���x


	static CPlayer *spInstance; //�C���X�^���X�̃|�C���^

	CPlayer(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
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
