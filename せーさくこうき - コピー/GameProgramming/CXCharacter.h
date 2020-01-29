#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix44.h"

class CXCharacter{
public:
	CModelX*mpModel; //モデルデータ
	int mAnimationIndex; //アニメーション番号
	bool mAnimationLoopFlg; //true：繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize; //アニメーションの再生フレーム数
	CVector3 mPosition; //位置
	CVector3 mRotation; //回転値
	CMatrix44 mMatrix; //位置回転行列


	//初期化処理
	void Init(CModelX*model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix44 &m);

	void Update();
	//描画処理
	void Render();
};

#endif