#ifndef CPLAYER_H
#define CPLAYER_H

#include "CCharacter.h"
//?
#include "CXCharacter.h"
/*
プレイヤークラス
*/
class CPlayer : public CCharacter {
public:
	//?
	CXCharacter mXCharacter;
	void Render();

	//球コライダ追加
	CSphereCollider mColSphere;
	//移動速度
	CVector3 mVelocity;

	int Jump = 0; //ジャンプ回数
	int Goal = 1; //ゴール条件 1クリア　2失敗
	int Happy = 0; //ハッピー状態
	int Time = 0 * 60; //タイム

	int x = 0;
	int z = 0;//速度


	static CPlayer *spInstance; //インスタンスのポインタ

	CPlayer(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
		//親のクラスを初期化
		: CCharacter(x, y, z, w, h, d, rx, ry, rz)
	{
		//?
		//
		mTaskTag = EPLAYER;
		//球コライダの設定
		//このタスクを設定
		mColSphere.mpTask = this;
		//合成行列の設定
		mColSphere.mpMatrix = &mBox.mMatrix;
		//球の半径の長さ設定
		mColSphere.mRadius = w;
		//?
		mColSphere.mPosition = CVector3(0.0f, 1.0f, 0.0f);

		spInstance = this;
	}

	//更新処理
	void Update();
	//衝突処理
	void OnCollision(C3DCollider *i, C3DCollider *y);
};

#endif
