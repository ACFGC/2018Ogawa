#pragma once

#include "glut.h"

#define W_H		800 //Window��
#define W_V		600 //Window����

//�^�X�N�}�l�[�W���C���N���[�h
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
		//�^�X�N�Ǘ��̔j��
		CTaskManager::Get()->Destroy();
		//�ՓˊǗ��̔j��
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

