#ifndef CTASK_H
#define CTASK_H

#include "CMatrix44.h"
#include "CCollider.h"

class CTask;

/*
タスク管理クラスの定義
*/
class CTaskManager {
private:
	//privateのメンバは、自分のクラスだけアクセスできる
	//インスタンスのポインタ
	static CTaskManager *mpInstance;
	//先頭ポインタ
	CTask *mpHead;
	//最終ポインタ
	CTask *mpTail;
	CTaskManager()
		: mpHead(0)
		, mpTail(0)
	{}
public:
	//publicのメンバは、全てのクラスからアクセスできる
	//インスタンスの取得
	static CTaskManager* Get();
	//タスクをリストへ追加する
	void Add(CTask *p);
	//タスクの更新
	void Update();
	//タスクの描画
	void Render();
	//破棄処理
	void Destroy();
	//項目削除処理
	void Delete();
	//項目をリストから削除
	void Remove(CTask*);
};


class CTask {
public:
	//タスクの識別値
	enum ETaskTag {
		EPLAYER,	//プレイヤー
		EOBJECT,
		EGOAL,
		EHAPPY,
		EWIND,
	};
	//タスクの識別
	ETaskTag mTaskTag;
	//有効フラグ
	bool mEnabled;
	//次のタスクへのポインタ
	CTask *mpNext;
	CTask *mpPrev;
	//合成行列
	CMatrix44 mMatrix;
	//コンストラクタ
	CTask()
		: mEnabled(true)
		, mpNext(0)
		, mpPrev(0)
	{
		//タスクリストに追加
		CTaskManager::Get()->Add(this);
	}
	virtual ~CTask() {
		//タスクリストから削除
		CTaskManager::Get()->Remove(this);
	}
	//初期化処理
	virtual void Init() {};
	//更新処理
	virtual void Update() {};
	//描画処理
	virtual void Render() {};
	//衝突処理
	virtual void OnCollision(C3DCollider *i, C3DCollider *y) {};
};

#endif
