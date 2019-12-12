#include "CWind.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CWind *CWind::spInstance = 0;

void CWind::Update() {
	//更新
	CCharacter::Update();
}
/*
衝突処理
i:自分のコライダ
y:相手のコライダ
*/
void CWind::OnCollision(C3DCollider *i, C3DCollider *y) {
	//衝突判定処理を呼ぶ
	if (C3DCollider::Collision(i, y)) {
		//衝突している時
		switch (i->mTag) {
			//自分のコライダが球
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//相手のコライダがボックス
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