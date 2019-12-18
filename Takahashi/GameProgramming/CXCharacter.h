#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix44.h"
//コライダクラスの宣言
class CCollider;

class CXCharacter {
public:
	//キャラクターの識別
	enum ECharTag {
		EPLAYER = 1, //1から順番
		EENEMY,
	};
	ECharTag mTag;	//キャラクタ識別タグ

	CModelX *mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize;//アニメーションの再生フレーム数
	CVector3 mPosition;	//位置
	CVector3 mRotation;	//回転値
	CMatrix44 mMatrix;	//位置回転行列
	float mVelocityG; //重力速度

	//初期化処理
	void Init(CModelX *model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	//更新処理
	void Update(CMatrix44 &m);
	void Update();
	//描画処理
	void Render();
	//衝突処理
	virtual bool Collision(CCollider*, CCollider*){
		return false;
	};
	// 重力処理
	void Gravity();


};

#endif

