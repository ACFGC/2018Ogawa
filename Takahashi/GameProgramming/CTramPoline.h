#ifndef CTRAMPOLINE_H
#define CTRAMPOLINE_H

#include "CCharacter.h"

/*
プレイヤークラス
*/
class CTrampoline : public CCharacter {
public:

	//球コライダ追加
	CSphereCollider mColSphere;

	static CTrampoline *spInstance; //インスタンスのポインタ

	CTrampoline(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
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