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

	//位置を更新
	mPosition = mPosition + mVelocity;
	//更新
	CCharacter::Update();
}
/*
衝突処理
i:自分のコライダ
y:相手のコライダ
*/
void CHammer::OnCollision(C3DCollider *i, C3DCollider *y) {
	//衝突判定処理を呼ぶ
	if (C3DCollider::Collision(i, y)) {
		//衝突している時
		switch (i->mTag) {
			//自分のコライダが球
		case C3DCollider::E3DBOX:
			switch (y->mTag) {
				//相手のコライダがボックス
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