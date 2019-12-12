#ifndef CMOVE_H
#define CMOVE_H

#include "CCharacter.h"
#include "CBall.h"
/*
プレイヤークラス
*/
class CMove : public CCharacter {
public:
	//球コライダ追加
	CSphereCollider mColSphere;
	//移動速度
	CVector3 mVelocity;

	int change = 0; //移動方向
	int Move = 60;  //移動時間


	static CMove *spInstance; //インスタンスのポインタ

	CMove(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
		//親のクラスを初期化
		: CCharacter(x, y, z, w, h, d, rx, ry, rz)
	{
		//球コライダの設定
		//このタスクを設定
		mColSphere.mpTask = this;
		//合成行列の設定
		mColSphere.mpMatrix = &mBox.mMatrix;
		//球の半径の長さ設定
		mColSphere.mRadius = w;

		spInstance = this;
	}

	//更新処理
	void Update();
	//衝突処理
	void OnCollision(C3DCollider *i, C3DCollider *y);
};

#endif
