#include "CMatrix33.h"
#include <stdio.h>	//printfのインクルード
#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード
/*
 Identity()
 単位行列を作成する
*/
void CMatrix33::Identity() {
	//2次元配列m全体を0クリア
	memset(m, 0, sizeof(m));
	//斜め下の対角線上に1設定
	m[0][0] = m[1][1] = m[2][2] = 1.0f;
}
/*
m[0][0] m[0][1] m[0][2]
m[1][0] m[1][1] m[1][2]
m[2][0] m[2][1] m[2][2]
の設定値をコンソール出力する
*/
void CMatrix33::Print() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			//m[i][j]の値を出力する
			//%f float型の値に置き換える
			printf("%f ", m[i][j]);
		}
		//改行する \n 改行
		printf("\n");
	}
}

//回転行列の設定
void CMatrix33::SetRotation(float degree) {
	//度からラジアンに変換する
	float radian = degree * M_PI / 180.0f;
	//サインを求める
	float sin = sinf(radian);
	//コサインを求める
	float cos = cosf(radian);
	//単位行列にする
	Identity();
	//回転値の設定
	m[0][0] = m[1][1] = cos;
	m[0][1] = -sin;
	m[1][0] = sin;
}
//2次元ベクトルクラスを掛ける
const CVector2 CMatrix33::MultiVector2(const CVector2 &v) const {
	CVector2 vector;
	vector.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2];
	vector.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2];
	return vector;
}
// *演算子のオーバーロード
const CVector2 CMatrix33::operator*(const CVector2 &v) const {
	return MultiVector2(v);
}

//移動行列の設定
void CMatrix33::SetTranslate(float x, float y) {
	//単位行列に設定
	Identity();
	//移動量設定
	m[0][2] = x;
	m[1][2] = y;
}
//3行3列行列クラスを掛ける
const CMatrix33 CMatrix33::MultiMatrix33(const CMatrix33 &a) const {
	CMatrix33 r;
	r.m[0][0] = m[0][0] * a.m[0][0] + m[0][1] * a.m[1][0] + m[0][2] * a.m[2][0];
	r.m[0][1] = m[0][0] * a.m[0][1] + m[0][1] * a.m[1][1] + m[0][2] * a.m[2][1];
	r.m[0][2] = m[0][0] * a.m[0][2] + m[0][1] * a.m[1][2] + m[0][2] * a.m[2][2];

	r.m[1][0] = m[1][0] * a.m[0][0] + m[1][1] * a.m[1][0] + m[1][2] * a.m[2][0];
	r.m[1][1] = m[1][0] * a.m[0][1] + m[1][1] * a.m[1][1] + m[1][2] * a.m[2][1];
	r.m[1][2] = m[1][0] * a.m[0][2] + m[1][1] * a.m[1][2] + m[1][2] * a.m[2][2];

	r.m[2][0] = m[2][0] * a.m[0][0] + m[2][1] * a.m[1][0] + m[2][2] * a.m[2][0];
	r.m[2][1] = m[2][0] * a.m[0][1] + m[2][1] * a.m[1][1] + m[2][2] * a.m[2][1];
	r.m[2][2] = m[2][0] * a.m[0][2] + m[2][1] * a.m[1][2] + m[2][2] * a.m[2][2];

	return r;
}

// *演算子のオーバーロード
const CMatrix33 CMatrix33::operator*(const CMatrix33 &a) const {
	return MultiMatrix33(a);
}

//拡大縮小行列の設定
void CMatrix33::SetScale(float x, float y) {
	//単位行列に設定
	Identity();
	m[0][0] = x;
	m[1][1] = y;
}
