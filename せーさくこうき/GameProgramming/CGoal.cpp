#include "CGoal.h"
#include "CCollider.h"
#include "CKey.h"
#include "CPlayer.h"

CGoal *CGoal::spInstance = 0;

void CGoal::Update() {
	//更新
	CCharacter::Update();
}
/*
衝突処理
i:自分のコライダ
y:相手のコライダ
*/
void CGoal::OnCollision(C3DCollider *i, C3DCollider *y) {
	//衝突判定処理を呼ぶ
	if (C3DCollider::Collision(i, y)) {
		//衝突している時
		switch (i->mTag) {
			//自分のコライダが球
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//相手のコライダがボックス
			case C3DCollider::ESPHERE:
				if (CPlayer::spInstance->Goal > 0){
					CPlayer::spInstance->Goal -= 1;
				}
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