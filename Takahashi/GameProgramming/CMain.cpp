//ヘッダファイルのインクルード
#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード
#include <stdio.h>
#include "windows.h"
#include "CMain.h"

//初めに1回だけ実行する処理の定義
void CMain::Init() {
	mpScene = new CScene();
	mpScene->Init();
}
//繰り返し実行する処理の定義
void CMain::Update() {
	mpScene->Update();
}
