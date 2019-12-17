#include "CPlayer.h"
#include "CCollider.h"
#include "CKey.h"
#include <Windows.h>

CPlayer *CPlayer::spInstance = 0;

void CPlayer::Update() {
	/*
	�L�[���͏���
	*/
	if (Happy == 0 && Goal > 0){
		if (CKey::Once(' ')) {
			if (Jump <= 1){
				mVelocity.y = 0.5;
				//�W�����v�g�p�s��
				Jump += 1;
			}
		}
		if (mVelocity.z > -0.2){
			if (CKey::Push('W') || CKey::Push(VK_UP)) {
				mVelocity.z -= 0.005;
				
				//z -= 0.002;
				//smPosition = mPosition -mBox.mMatrixRotation*mBox.mForward;
			}
		}
		if (mVelocity.z < 0.2){
			if (CKey::Push('S') || CKey::Push(VK_DOWN)) {
				mVelocity.z += 0.005;
			}
		}
		if (mVelocity.x > -0.2){
			if (CKey::Push('A') || CKey::Push(VK_LEFT)) {
				mVelocity.x -= 0.005;
			}
		}
		if (mVelocity.x < 0.2){
			if (CKey::Push('D') || CKey::Push(VK_RIGHT)) {
				mVelocity.x += 0.005;
			}
		}
	}
	//�n�b�s�[���
	else if (Happy>0 && Goal > 0) {
		mVelocity.x = 0;
		mVelocity.z = 0;
		if (CKey::Once(' ') && Jump <= 1) {
			mVelocity.y = 1.0;
			//�W�����v�g�p�s��
			Jump += 1;
		}
		if (Jump == 0){
			mVelocity.y = 1.0;
			Jump += 1;
		}
		if (CKey::Push('W') || CKey::Push(VK_UP)) {
				mVelocity.z = -0.3;
			}
		if (CKey::Push('S') || CKey::Push(VK_DOWN)) {
				mVelocity.z =  0.3;
			}
		if (CKey::Push('A') || CKey::Push(VK_LEFT)) {
				mVelocity.x = -0.3;
			}
		if (CKey::Push('D') || CKey::Push(VK_RIGHT)) {
				mVelocity.x =  0.3;
			}
	}

	/*
	//���G���A�̒�
	if (Wind > 0){
		if (mVelocity.x < 0.2){
			mVelocity.x += 0.001;
		}
	}
	*/

	//�d�͉����x���Z
	mVelocity.y -= 0.02f;
	//�n�b�s�[��Ԑ�������
	if (Happy > 0){
		Happy -= 1;
	}
	

	if (CKey::Push('J')){
		mBox.LeftTurn();
	}

	if (CKey::Push('L')){
		mBox.RightTurn();
	}
	

	//����
	if (mVelocity.x > 0){
		mVelocity.x -= 0.0005f;
	}
	if (mVelocity.x < 0){
		mVelocity.x += 0.0005f;
	}

	if (mVelocity.z > 0){
		mVelocity.z -= 0.0005f;
	}
	if (mVelocity.z < 0){
		mVelocity.z += 0.0005f;
	}



	//�W�����v�񐔐���
	if (Jump <= 1)
		Jump = 1;
	else if (Jump > 1)
		Jump = 2;

	//�^�C���ݒ�
	//�S�[�����ĂȂ��Ƒ���
	if (Goal == 1)
	Time += 1;

	//�S�[��������
	if (Goal <= 0){
		mVelocity.x = 0;
		mVelocity.z = 0;
	}

	//�������玸�s
	if (mPosition.y < -30){
		Goal = 2;
	}

	//�d�͉����x���Z
	mVelocity.y -= 0.0002f;

	CMatrix44 mat;
	mat.SetRotationY(mBox.mRotation.y);
	CVector3 forward = mat*mVelocity;

	//�ʒu���X�V
	mPosition = mPosition + forward;

	//�X�V
	CCharacter::Update();
}
/*
�Փˏ���
i:�����̃R���C�_
y:����̃R���C�_
*/
void CPlayer::OnCollision(C3DCollider *i, C3DCollider *y) {
	int dx, dy,dz;
	//�Փ˔��菈�����Ă�
	//if (C3DCollider::Collision(i, y, &dx, &dy, &dz)) {
	//if (i->Collision((CSphereCollider*)y, &dx, &dy, &dz)) {
	if (i->Collision((CSphereCollider*)y)) {
			//�Փ˂��Ă��鎞
		switch (i->mTag) {
			//�����̃R���C�_����
		case C3DCollider::ESPHERE:
			switch (y->mTag) {
				//����̃R���C�_���{�b�N�X
			case C3DCollider::E3DBOX:
				switch (y->mTag){
				case CTask::EWIND:
					break;
				default:
					//�������̑��x��0�ɂ���
					mVelocity.y = 0.0f;
					//�߂荞�񂾕��߂�
					mPosition = mPosition - i->mAdjust;
					//�W�����v����
					Jump = 0;
					break;
				}
			
			default:
				;
			}
			break;
		default:
			;
		}
	}
}