#include "CTask.h"

//インスタンスのstatic変数
CTaskManager* CTaskManager::mpInstance = 0;
//インスタンスの取得
CTaskManager* CTaskManager::Get() {
	//インスタンスが無い(0)の時
	if (mpInstance == 0) {
		//インスタンスを作成して代入
		mpInstance = new CTaskManager();
	}
	//インスタンスのポインタを返す
	return mpInstance;
}

//リストへ追加
void CTaskManager::Add(CTask *p) {
	if (mpHead == 0) {
		//リストの最初
		//リストの先頭にする
		mpHead = p;
		mpHead->mpPrev = 0;
		//リストの最後にする
		mpTail = p;
		//最後の次は無しにする
		mpTail->mpNext = 0;
	}
	else {
		//最後に追加
		mpTail->mpNext = p;
		p->mpPrev = mpTail;
		mpTail = p;
		p->mpNext = 0;
	}
}

//更新処理
void CTaskManager::Update() {
	//リストのタスクをtaskで参照していく
	CTask *task = mpHead;
	//taskが0になったら終了
	while (task) {
		//更新処理
		task->Update();
		//次のリストへ
		task = task->mpNext;
	}
}

//描画処理
void CTaskManager::Render() {
	//リストのタスクをtaskで参照していく
	CTask *task = mpHead;
	//taskが0になったら終了
	while (task) {
		//描画処理
		task->Render();
		//次のリストへ
		task = task->mpNext;
	}
}

//破棄処理
void CTaskManager::Destroy() {
	//リストをcolで参照していく
	CTask *col = mpHead;
	//colが0になったら終了
	while (col) {
		//次のポインタを退避
		CTask *next = col->mpNext;
		//項目を削除
		delete col;
		//次のリストへ
		col = next;
	}
	//衝突管理のインスタンス削除
	delete mpInstance;
	//インスタンスへのポインタ初期化
	mpInstance = 0;
}

//項目削除処理
void CTaskManager::Delete() {
	//前の項目のポインタ
	CTask *prev = 0;
	//リストをcolで参照していく
	CTask *col = mpHead;
	//colの所有者が無効な項目は削除
	while (col) {
		//無効か判定
		if (!col->mEnabled) {
			CTask *next = col->mpNext;
			delete col;
			col = next;
		}
		else {
			//有効な場合は次へ
			prev = col;
			col = col->mpNext;
		}
	}
	//最終の項目を更新
	mpTail = prev;
	if (mpTail)
		mpTail->mpNext = 0;
}

void CTaskManager::Remove(CTask* p) {
	if (p == mpHead) {
		mpHead = p->mpNext;
		if (mpHead)
			mpHead->mpPrev = 0;
		else
			mpTail = 0;
	}
	else if (p == mpTail) {
		mpTail = p->mpPrev;
		if (mpTail)
			mpTail->mpNext = 0;
	}
	else {
		p->mpPrev->mpNext = p->mpNext;
		p->mpNext->mpPrev = p->mpPrev;
	}
}
