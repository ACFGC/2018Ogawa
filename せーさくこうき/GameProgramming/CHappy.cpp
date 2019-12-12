#include "CHappy.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CHappy *CHappy::spInstance = 0;

void CHappy::Update() {
	//更新
	CCharacter::Update();
}
/*
衝突処理
i:自分のコライダ
y:相手のコライダ
*/
void CHappy::OnCollision(C3DCollider *i, C3DCollider *y) {
	//衝突判定処理を呼ぶ
	if (C3DCollider::Collision(i, y)) {
		//衝突している時
		switch (i->mTag) {
			//自分のコライダが球
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//相手のコライダがボックス
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