#ifndef C3DBOX_H
#define C3DBOX_H
//三角形クラスのインクルード
#include "C3DTriangle.h"
/*
直方体クラス
*/
class C3DBox {
public:
	//色 0:赤 1:緑 2:青 3:アルファ
	float mDiffuse[4];
	float w;	//幅
	float h;	//高さ
	float d;	//奥行き
	//三角形12個
	C3DTriangle mTriangle[12];
	//回転値
	CVector3 mRotation;
	//回転行列
	CMatrix44 mMatrixRotation;
	//位置
	CVector3 mPosition;
	//移動行列
	CMatrix44 mMatrixTranslate;
	//合成行列
	CMatrix44 mMatrix;
	//進行方向
	CVector3 mForward;
	//進行の速さ
	float mVelocity;
	C3DBox()
		: mVelocity(5.0f)
	{}
	//直方体の設定
	void SetWHD(float w, float h, float d);
	//直方体の描画
	void Render();
	//更新処理
	void Update();
	//前進処理
	void Forward();
	//回転
	void LeftTurn();
	void RightTurn();
	//拡散光の設定
	void SetDiffuse(float r, float g, float b, float a);
};

#endif
