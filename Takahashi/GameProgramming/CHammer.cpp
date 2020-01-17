#include "CHammer.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CHammer *CHammer::spInstance = 0;

void CHammer::Update() {
	mBox.mRotation.x += 1;

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