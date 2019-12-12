#include "CHammer.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CHammer *CHammer::spInstance = 0;

void CHammer::Update() {
	if (change == 0){
		mVelocity.x = 0.5f;
	}
	else if (change == 1){
		mVelocity.x = -0.5f;
	}

	if (Move == 0){
		if (change == 0){
			change = 1;
		}
		else if (change == 1){
			change = 0;
		}
		Move = 1 * 60;
	}
	Move--;

	//�ʒu���X�V
	mPosition = mPosition + mVelocity;
	//�X�V
	CCharacter::Update();
}
/*
�Փˏ���
i:�����̃R���C�_
y:����̃R���C�_
*/
void CHammer::OnCollision(C3DCollider *i, C3DCollider *y) {
	//�Փ˔��菈�����Ă�
	if (C3DCollider::Collision(i, y)) {
		//�Փ˂��Ă��鎞
		switch (i->mTag) {
			//�����̃R���C�_����
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//����̃R���C�_���{�b�N�X
			case C3DCollider::ESPHERE:
				break;
			default:
				;
			}
			break;
		default:
			;
		}
	}
}