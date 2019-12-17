#include "CPlayer.h"
#include "CCollider.h"
#include "CKey.h"
#include <Windows.h>

CPlayer *CPlayer::spInstance = 0;

void CPlayer::Update() {
	/*
	キー入力処理
	*/
	if (Happy == 0 && Goal > 0){
		if (CKey::Once(' ')) {
			if (Jump <= 1){
				mVelocity.y = 0.5;
				//ジャンプ使用不可
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
	//ハッピー状態
	else if (Happy>0 && Goal > 0) {
		mVelocity.x = 0;
		mVelocity.z = 0;
		if (CKey::Once(' ') && Jump <= 1) {
			mVelocity.y = 1.0;
			//ジャンプ使用不可
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
	//風エリアの中
	if (Wind > 0){
		if (mVelocity.x < 0.2){
			mVelocity.x += 0.001;
		}
	}
	*/

	//重力加速度加算
	mVelocity.y -= 0.02f;
	//ハッピー状態制限時間
	if (Happy > 0){
		Happy -= 1;
	}
	

	if (CKey::Push('J')){
		mBox.LeftTurn();
	}

	if (CKey::Push('L')){
		mBox.RightTurn();
	}
	

	//減速
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



	//ジャンプ回数制限
	if (Jump <= 1)
		Jump = 1;
	else if (Jump > 1)
		Jump = 2;

	//タイム設定
	//ゴールしてないと増加
	if (Goal == 1)
	Time += 1;

	//ゴールしたら
	if (Goal <= 0){
		mVelocity.x = 0;
		mVelocity.z = 0;
	}

	//落ちたら失敗
	if (mPosition.y < -30){
		Goal = 2;
	}

	//重力加速度加算
	mVelocity.y -= 0.0002f;

	CMatrix44 mat;
	mat.SetRotationY(mBox.mRotation.y);
	CVector3 forward = mat*mVelocity;

	//位置を更新
	mPosition = mPosition + forward;

	//更新
	CCharacter::Update();
}
/*
衝突処理
i:自分のコライダ
y:相手のコライダ
*/
void CPlayer::OnCollision(C3DCollider *i, C3DCollider *y) {
	int dx, dy,dz;
	//衝突判定処理を呼ぶ
	//if (C3DCollider::Collision(i, y, &dx, &dy, &dz)) {
	//if (i->Collision((CSphereCollider*)y, &dx, &dy, &dz)) {
	if (i->Collision((CSphereCollider*)y)) {
			//衝突している時
		switch (i->mTag) {
			//自分のコライダが球
		case C3DCollider::ESPHERE:
			switch (y->mTag) {
				//相手のコライダがボックス
			case C3DCollider::E3DBOX:
				switch (y->mTag){
				case CTask::EWIND:
					break;
				default:
					//下向きの速度を0にする
					mVelocity.y = 0.0f;
					//めり込んだ分戻す
					mPosition = mPosition - i->mAdjust;
					//ジャンプ復活
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