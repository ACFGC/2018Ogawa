#ifndef CCHARACTER_H
#define CCHARACTER_H

#include "CTask.h"
#include "C3DBox.h"
#include "CCollider.h"

//キャラクタの基本クラス
class CCharacter : public CTask {
public:
	//四角形追加
	C3DBox mBox;
	//四角形コライダ追加
	C3DBoxCollider mBoxCol;
	//位置
	CVector3 mPosition;
	CVector3 mRotation;
	//デフォルトコンストラクタ
	CCharacter() {
		//四角形初期化
		mBox.SetWHD(1.0f, 1.0f, 1.0f);
		//コライダ初期化
		mBoxCol.mpTask = this;
		mBoxCol.mSize = CVector3(1.0f, 1.0f, 1.0f);		
		mBoxCol.mpMatrix = &mBox.mMatrix;
	}
	/*
	コンストラクタ
	x:X座標、y:Y座標、z:Z座標
	w:幅、h:高さ、d:奥行
	*/
	CCharacter(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz ) {
		//四角形設定
		mBox.SetWHD(w, h, d);
		mBox.SetDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
		mPosition = mBox.mPosition = CVector3(x, y, z);
		mRotation = mBox.mRotation = CVector3(rx, ry, rz);
		//コライダ設定
		//このタスクを設定
		mBoxCol.mpTask = this;
		//コライダの大きさを設定
		mBoxCol.mSize = CVector3(w, h, d);
		//合成行列を設定
		mBoxCol.mpMatrix = &mBox.mMatrix;
	}

	virtual ~CCharacter() {
	}

	void Update() {
		//四角形更新
		mBox.mPosition = mPosition;
		mBox.Update();
	}

	void Render() {
		//四角形描画
		mBox.Render();
	};

};

#endif
