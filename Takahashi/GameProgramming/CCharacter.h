#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CTask.h"
#include "C3DBox.h"
#include "CCollider.h"

//�L�����N�^�̊�{�N���X
class CCharacter : public CTask {
public:
	//�l�p�`�ǉ�
	C3DBox mBox;
	//�l�p�`�R���C�_�ǉ�
	C3DBoxCollider mBoxCol;
	//�ʒu
	CVector3 mPosition;
	CVector3 mRotation;
	//�f�t�H���g�R���X�g���N�^
	CCharacter() {
		//�l�p�`������
		mBox.SetWHD(1.0f, 1.0f, 1.0f);
		//�R���C�_������
		mBoxCol.mpTask = this;
		mBoxCol.mSize = CVector3(1.0f, 1.0f, 1.0f);		
		mBoxCol.mpMatrix = &mBox.mMatrix;
	}
	/*
	�R���X�g���N�^
	x:X���W�Ay:Y���W�Az:Z���W
	w:���Ah:�����Ad:���s
	*/
	CCharacter(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz ) {
		//�l�p�`�ݒ�
		mBox.SetWHD(w, h, d);
		mBox.SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		mPosition = mBox.mPosition = CVector3(x, y, z);
		mRotation = mBox.mRotation = CVector3(rx, ry, rz);
		//�R���C�_�ݒ�
		//���̃^�X�N��ݒ�
		mBoxCol.mpTask = this;
		//�R���C�_�̑傫����ݒ�
		mBoxCol.mSize = CVector3(w, h, d);
		//�����s���ݒ�
		mBoxCol.mpMatrix = &mBox.mMatrix;
	}

	virtual ~CCharacter() {
	}

	void Update() {
		//�l�p�`�X�V
		mBox.mPosition = mPosition;
		mBox.Update();
	}

	void Render() {
		//�l�p�`�`��
		mBox.Render();
	};

};

#endif
