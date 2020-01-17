#pragma once

#include "glut.h"

#define W_H		800 //Window幅
#define W_V		600 //Window高さ

//タスクマネージャインクルード
#include "CTask.h"
#include "CScene.h"

class CMain {
	int		mState;
public:
	CScene *mpScene;
	CMain() : mState(0), mpScene(0) {}

	~CMain() {
		if (mpScene) {
			delete mpScene;
		}
		//タスク管理の破棄
		CTaskManager::Get()->Destroy();
		//衝突管理の破棄
		CCollisionManager::Get()->Destroy();
	}

	void MainLoop() {
		switch (mState)
		{
		case 0:
			Init();
			mState = 1;
			break;
		default:
			Update();
			break;
		}
	}
	void Init();
	void Update();

};

