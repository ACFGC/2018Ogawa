//�w�b�_�t�@�C���̃C���N���[�h
#define _USE_MATH_DEFINES	//���w���C�u������M_PI��L���ɂ���
#include <math.h>	//���w���C�u�����̃C���N���[�h
#include <stdio.h>
#include "windows.h"
#include "CMain.h"

//���߂�1�񂾂����s���鏈���̒�`
void CMain::Init() {
	mpScene = new CScene();
	mpScene->Init();
}
//�J��Ԃ����s���鏈���̒�`
void CMain::Update() {
	mpScene->Update();
}
