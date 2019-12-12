#include "CWind.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CWind *CWind::spInstance = 0;

void CWind::Update() {
	//�X�V
	CCharacter::Update();
}
/*
�Փˏ���
i:�����̃R���C�_
y:����̃R���C�_
*/
void CWind::OnCollision(C3DCollider *i, C3DCollider *y) {
	//�Փ˔��菈�����Ă�
	if (C3DCollider::Collision(i, y)) {
		//�Փ˂��Ă��鎞
		switch (i->mTag) {
			//�����̃R���C�_����
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//����̃R���C�_���{�b�N�X
			case C3DCollider::ESPHERE:
				CPlayer::spInstance->mVelocity.x += 0.005;
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