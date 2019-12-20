#include "CScene.h"

#include "CCharacter.h"
#include "CPlayer.h"
#include "CBreak.h"
#include "CGoal.h"
#include "CHappy.h"
#include "CWind.h"
#include "CTramPoline.h"
#include "CMove.h"
#include "CHammer.h"
#include "CInput.h"
#include <stdio.h>


//初めに1回だけ実行する処理の定義
void CScene::Init() {
	//?
	mModelX.Load("ラグナ.x");
//	mXPlayer.Init(&mModelX);
//	mXPlayer.mPosition = CVector3(00.0f, 20.0f, 40.0f);

	//床生成
	new CCharacter(0.0f, 0.0f, 50.0f, 20.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//床生成
	new CCharacter(0.0f, 0.0f, -20.0f, 20.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//床生成
	new CCharacter(0.0f, 0.0f, -100.0f, 20.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//床生成
	new CCharacter(-10.0f, 0.0f, -180.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//床生成
	new CCharacter(-10.0f, 0.0f, -240.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	//床生成
	new CCharacter(-10.0f, 0.0f, -320.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);

	//プレイヤー生成
	CPlayer *player = new CPlayer(0.0f, 50.0f, 50.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	player->mXCharacter.Init(&mModelX);

	 //ゴール生成
	//new CGoal(0.0f, 30.0f, -160.0f, 20.0f, 30.0f, 20.0f, 0.0f, 0.0f, 0.0f);

	//ハッピーゾーン生成
	new CHappy(-20.0f, 3.0f, 30.0f, 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 0.0f);

	//坂生成
	new CCharacter(1.0f, 5.0f, 10.0f, 10.0f, 1.0f, 10.0f, 30.0f, 0.0f, 0.0f);
	//壁生成
	new CCharacter(20.0f, 10.0f, 0.0f, 20.0f, 1.0f, 10.0f, 90.0f, 90.0f, .0f);

	//トランポリン生成
	new CTrampoline(0.0f, 0.0f, -60.0f, 10.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f);

	//風エリア
	new CWind(0.0f, 00.0f, -140.0f, 10.0f, 1.0f, 10.0f, 0.0f, 0.0f, 0.0f);

	//動く床
	new CMove(-30.0f, 10.0f, -210.0f, 10.0f, 10.0f, 1.0f, 0.0f, 0.0f, 0.0f);

	//回転床
	new CHammer(0.0f, 10.0f, 30.0f, 10.0f, 10.0f, 1.0f, 0.0f, 90.0f, 0.0f);

	//消えるブロック生成
	new CBreak(-10.0f, 0.0f, -280.0f, 5.0f, 1.0f, 20.0f, 0.0f, 0.0f, 0.0f);
	/*	new CBreak(2.0f, 15.0f, -10.0f, 1.0f, 1.0f, 1.0f);
	new CBreak(4.0f, 10.0f, -10.0f, 1.0f, 1.0f, 1.0f);
	*/
}

//繰り返し実行する処理の定義
void CScene::Update() {
	//?
//	mXPlayer.Update();

	//タスクを更新していく
	CTaskManager::Get()->Update();
	//衝突処理
	CCollisionManager::Get()->Update();
	//無効なタスクを削除していく
	CTaskManager::Get()->Delete();

	//マウスの左ボタン押されているか 
	if (CInput::GetMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
		//マウス座標変数作成 
		float x, y;
		//マウスカーソルの座標取得 
		CInput::GetCursorPos(&x, &y);
		//座標をコンソールに表示 
		printf("%10f %10f\n", x, y);
	}

	
	CVector3 eye = CPlayer::spInstance->mBox.mMatrix * CVector3(0.0f, 3.0f, 10.0f);
	//視点の設定（カメラの設定）
	//gluLookAt(目の位置(x,y,z)，目標の位置(x,y,z)，上方向(x,y,z))
	gluLookAt(eye.x, eye.y, eye.z, CPlayer::spInstance->mPosition.x, CPlayer::spInstance->mPosition.y, CPlayer::spInstance->mPosition.z, 0.0f, 1.0f, 0.0f);

	static GLfloat lightPosition[4] = { 200.0, 200.0, 20.0, 5.0 }; //光源の位置
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //光源位置の設定

	//タスクを描画していく
	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();
	//?
//	mXPlayer.Render();

	//2D座標でUIを描画
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();		//プロジェクション行列を退避
	glLoadIdentity();	//プロジェクション行列を初期化
	//プロジェクション行列を800×600に設定
	gluOrtho2D(-400, 400, -300, 300);
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();		//モデルビュー行列を退避
	glLoadIdentity();	//モデルビュー行列を初期化

	glDisable(GL_LIGHTING);	//ライト無効
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	//描画色

	char buf[10];
	//文字列設定
	mText.DrawString("SPACE:Jump W:Front A:< S:Back D:>", -350, 250, 10, 20);	//文字列描画

	//ゴールに触れると
	if (CPlayer::spInstance->Goal <= 0){
		mText.DrawString("Goal!", -220, 0, 60, 60);//文字列描画
	}

	//落ちると
	//ゴールに触れると
	if (CPlayer::spInstance->Goal >= 2){
		mText.DrawString("Failure", -220, 0, 40, 40);//文字列描画
	}

	//ハッピー状態の時間
	mText.DrawString("Happy:", -350, -250, 10, 20);	//文字列描画
	sprintf(buf, "%d", (CPlayer::spInstance->Happy+59)/60);
	mText.DrawString(buf, -220, -250, 10, 20);	//文字列描画

	//タイム表示
	mText.DrawString("Time:", 240, -250, 10, 20);	//文字列描画
	sprintf(buf, "%d", (CPlayer::spInstance->Time + 59) / 60);
	mText.DrawString(buf, 350, -250, 10, 20);	//文字列描画

	glEnable(GL_LIGHTING);	//ライド有効

	glPopMatrix();	//モデルビュー描画行列を戻す
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();	//プロジェクション行列を戻す
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);

}
