#ifndef CBREAK_H
#define CBREAK_H

#include "CCharacter.h"
/*
当たると消えるブロックのクラス
*/
class CBreak : public CCharacter {
public:
	CBreak(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
		//親のクラスを初期化
		: CCharacter(x, y, z, w, h, d, rx, ry, rz)
	{}
	//衝突処理
	void OnCollision(C3DCollider *i, C3DCollider *y) {
		//衝突判定を呼ぶ
		if (C3DCollider::Collision(i, y)) {
			CPlayer::spInstance->mVelocity.y = 0.5;
			//衝突していたら無効にする
			mEnabled = false;
		}
	}
};


#endif
