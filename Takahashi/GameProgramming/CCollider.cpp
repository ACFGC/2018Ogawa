#include "CCollider.h"
#include "CTask.h"
//?
#include "glut.h"
#include "C3DBox.h"

//インスタンスのstatic変数
CCollisionManager* CCollisionManager::mpInstance = 0;
//インスタンスの取得
CCollisionManager* CCollisionManager::Get() {
	//インスタンスが無い(0)の時
	if (mpInstance == 0) {
		//インスタンスを作成して代入
		mpInstance = new CCollisionManager();
	}
	//インスタンスのポインタを返す
	return mpInstance;
}
//リストへ追加
void CCollisionManager::Add(C3DCollider *p) {
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

//破棄処理
void CCollisionManager::Destroy() {
	//リストのコライダをcolで参照していく
	C3DCollider *col = mpHead;
	//colが0になったら終了
	while (col) {
		//次のポインタを退避
		C3DCollider *next = col->mpNext;
		//項目を削除
		delete col;
		//次のリストへ
		col = next;
	}
	//最後を初期化
	mpTail = 0;
	//衝突管理のインスタンス削除
	delete mpInstance;
	//インスタンスへのポインタ初期化
	mpInstance = 0;
}

void CCollisionManager::Remove(C3DCollider* p) {
	if (p == mpHead) {
		mpHead = p->mpNext;
		if (mpHead)
			mpHead->mpPrev = 0;
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

//球と球の衝突判定
bool CSphereCollider::Collision(CSphereCollider *p2) {
	//コライダの中心座標を移動させます
	CVector3 pos1 = *mpMatrix * mPosition;
	CVector3 pos2 = *p2->mpMatrix * p2->mPosition;
	//中心と中心のベクトルを求めます
//	pos1 = pos1 - pos2;
	//pos1:相手　pos2:自分
	pos1 = pos2 - pos1;
	//ベクトルの長さと半径の大きさを比較します
	if (pos1.Length() < mRadius + p2->mRadius) {
		//衝突している
		mAdjust = pos1 * ((mRadius + p2->mRadius - pos1.Length()) / (mRadius + p2->mRadius));
		p2->mAdjust = mAdjust * -1;
		return true;
	}
	else {
		//衝突していない
		mAdjust = p2->mAdjust = CVector3(0.0f, 0.0f, 0.0f);
	}
	return false;
}
//直方体と球の衝突判定
bool C3DBoxCollider::Collision(CSphereCollider *p) {
	//直方体の中心座標を求める
	CVector3 center = *mpMatrix * mPosition;
	//直方体のX軸方向を求める
//	CVector3 vx = *mpMatrix * (CVector3(1.0f, 0.0f, 0.0f) + mPosition) - center;
	CVector3 vx = *mpMatrix * CVector3(1.0f, 0.0f, 0.0f) - *mpMatrix * CVector3(0.0f, 0.0f, 0.0f);
	//直方体のY軸方向を求める
//	CVector3 vy = *mpMatrix * (CVector3(0.0f, 1.0f, 0.0f) + mPosition) - center;
	CVector3 vy = *mpMatrix * CVector3(0.0f, 1.0f, 0.0f) - *mpMatrix * CVector3(0.0f, 0.0f, 0.0f);
	//直方体のZ軸方向を求める
//	CVector3 vz = *mpMatrix * (CVector3(0.0f, 0.0f, 1.0f) + mPosition) - center;
	CVector3 vz = *mpMatrix * CVector3(0.0f, 0.0f, 1.0f) - *mpMatrix * CVector3(0.0f, 0.0f, 0.0f);
	//直方体から球へのベクトルを求める
	CVector3 vBS = *p->mpMatrix*p->mPosition - center;
	//直方体から球へ、直方体のX軸に対する長さとの差を求める
	float dx = p->mRadius + mSize.x - fabs(vx.Dot(vBS));
	//直方体から球へ、直方体のY軸に対する長さとの差を求める
	float dy = p->mRadius + mSize.y - fabs(vy.Dot(vBS));
	//直方体から球へ、直方体のZ軸に対する長さとの差を求める
	float dz = p->mRadius + mSize.z - fabs(vz.Dot(vBS));
	//衝突しているか判定する
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		//戻す量が最小の軸で戻す
		if (dx > dy) {
			if (dy > dz) {
				//Z軸で戻す ｍAdjust：戻す値
				if (vz.Dot(vBS) > 0.0f) {
					//+方向
					mAdjust = vz * dz;
				}
				else {
					//-方向
					mAdjust =  vz * -dz;
				}
			}
			else {
				//Y軸で戻す
				if (vy.Dot(vBS) > 0.0f) {
					mAdjust = vy * dy;
				}
				else {
					mAdjust = vy * -dy;
				}
			}
		}
		else {
			if (dx > dz) {
				//Z軸で戻す
				if (vz.Dot(vBS) > 0.0f) {
					mAdjust = vz * dz;
				}
				else {
					mAdjust = vz * -dz;
				}
			}
			else {
				//X軸で戻す
				if (vx.Dot(vBS) > 0.0f) {
					mAdjust = vx * dx;
				}
				else {
					mAdjust = vx * -dx;
				}
			}
		}
		p->mAdjust = mAdjust * -1.0f;
		return true;
	}
	return false;
}
//コライダの衝突判定
void CCollisionManager::Update() {
	C3DCollider *col1 = mpHead;
	while (col1 != 0) {
		//col1からcol1以降の衝突を判定する
		for (C3DCollider *col2 = col1->mpNext; col2 != 0; col2 = col2->mpNext) {
			if (col1->mpTask != col2->mpTask) {
				col1->mpTask->OnCollision(col1, col2);
				col2->mpTask->OnCollision(col2, col1);
			}
		}
		//次のコライダへ
		col1 = col1->mpNext;
	}
}

void CCollisionManager::Render() {
	C3DCollider *col1 = mpHead;
	while (col1 != 0) {
		col1->Render();
		//次のコライダへ
		col1 = col1->mpNext;
	}
}



bool C3DCollider::Collision(C3DCollider* i, C3DCollider*y) {
	switch (i->mTag) {
	case E3DBOX:
		switch (y->mTag) {
		case ESPHERE:
			return ((C3DBoxCollider*)i)->Collision((CSphereCollider*)y);
			break;
		}
		break;
	case ESPHERE:
		switch (y->mTag) {
		case ESPHERE:
			return ((CSphereCollider*)i)->Collision((CSphereCollider*)y);
			break;
		case E3DBOX:
			return ((C3DBoxCollider*)y)->Collision((CSphereCollider*)i);
			break;
		}
		break;
	}
	return false;
}

void C3DBoxCollider::Render() {
	return;
	glPushMatrix();
	glMultMatrixf(mpMatrix->Transpose().m[0]);
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	C3DBox box;
	box.SetWHD(mSize.x, mSize.y, mSize.z);
	box.Render();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void CSphereCollider::Render() {
	glPushMatrix();
	glMultMatrixf(mpMatrix->Transpose().m[0]);
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	glutWireSphere(mRadius, 16, 16);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}


