#include "CHappy.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CHappy *CHappy::spInstance = 0;

void CHappy::Update() {
	//�X�V
	CCharacter::Update();
}
/*
�Փˏ���
i:�����̃R���C�_
y:����̃R���C�_
*/
void CHappy::OnCollision(C3DCollider *i, C3DCollider *y) {
	//�Փ˔��菈�����Ă�
	if (C3DCollider::Collision(i, y)) {
		//�Փ˂��Ă��鎞
		switch (i->mTag) {
			//�����̃R���C�_����
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//����̃R���C�_���{�b�N�X
			case C3DCollider::ESPHERE:
					CPlayer::spInstance->Happy += 20 * 60;
				mEnabled = false;
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