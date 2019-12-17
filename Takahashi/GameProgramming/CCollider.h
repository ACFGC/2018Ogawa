#ifndef CCOLLIDER_H
#define CCOLLIDER_H

//タスククラスの宣言
class CTask;
//球コライダの宣言
class CSphereCollider;
//3次元ベクトルのインクルード
#include "CVector3.h"
#include "CMatrix44.h"

class C3DCollider;

/*
衝突管理クラスの定義
*/
class CCollisionManager {
private:
	//privateのメンバは、自分のクラスだけアクセスできる
	//インスタンスのポインタ
	static CCollisionManager *mpInstance;
	//先頭ポインタ
	C3DCollider *mpHead;
	//最終ポインタ
	C3DCollider *mpTail;

	CCollisionManager()
		: mpHead(0)
		, mpTail(0)
	{}
public:
	//publicのメンバは、全てのクラスからアクセスできる
	//インスタンスの取得
	static CCollisionManager* Get();
	//コライダをリストへ追加する
	void Add(C3DCollider *p);
	//衝突処理
	void Update();
	//破棄処理
	void Destroy();
	//項目リストから削除処理
	void Remove(C3DCollider*);
};


/*
 3D用のコライダクラス
*/
class C3DCollider {
public:
	//コライダの型
	enum EColTag{
		E3DBOX,
		ESPHERE,
	};
	EColTag mTag;
	//所有者
	CTask *mpTask;
	//変換行列
	CMatrix44 *mpMatrix;
	//中心座標
	CVector3 mPosition;
	//調整データ
	CVector3 mAdjust;
	//次ポインタ
	C3DCollider *mpNext;
	//前ポインタ
	C3DCollider *mpPrev;
	//コンストラクタ
	C3DCollider()
		: mpNext(0)
		, mpPrev(0)
	{
		//リストに追加
		CCollisionManager::Get()->Add(this);
	}
	//デストラクタ
	virtual ~C3DCollider() {
		//リストから削除
		CCollisionManager::Get()->Remove(this);
	}
	//衝突判定処理
	virtual bool Collision(CSphereCollider *p, int*px, int*py, int*pz) { return false; };
	static bool Collision(C3DCollider*, C3DCollider*);
	virtual bool Collision(CSphereCollider *p) { return false; };
};
/*
 球コライダクラス
*/
class CSphereCollider : public C3DCollider {
public:
	//半径
	float mRadius;
	CSphereCollider()
	{
		//球コライダ設定
		mTag = ESPHERE;
	}
	//衝突判定処理
//	bool Collision(CSphereCollider *p, int*px, int*py, int*pz);
	bool CSphereCollider::Collision(CSphereCollider *p2);
};
/*
 直方体コライダクラス
*/
class C3DBoxCollider : public C3DCollider {
public:
	//直方体の大きさ x:幅 y:高さ z:奥行
	CVector3 mSize;
	C3DBoxCollider()
	{
		//四角形コライダ設定
		mTag = E3DBOX;
	}
	//直方体と球の衝突判定
//	bool Collision(CSphereCollider *p, int*px, int*py, int*pz);
	bool C3DBoxCollider::Collision(CSphereCollider *p);
};



#endif
