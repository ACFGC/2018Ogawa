#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード
#include "CMatrix44.h"
#include <stdio.h>

void CMatrix44::Identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j) {
				m[i][j] = 1.0f;
			}
			else {
				m[i][j] = 0.0f;
			}
		}
	}
}

void CMatrix44::Print() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%9f ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//回転行列の設定
void CMatrix44::SetRotationY(float degree) {
	//度からラジアンに変換する
	float radian = degree * M_PI / 180.0f;
	//サインを求める
	float sin = sinf(radian);
	//コサインを求める
	float cos = cosf(radian);
	//単位行列にする
	Identity();
	//回転値の設定
	m[0][0] = m[2][2] = cos;
	m[0][2] = sin;
	m[2][0] = -sin;
}

//回転行列の設定
void CMatrix44::SetRotationX(float degree) {
	//度からラジアンに変換する
	float radian = degree * M_PI / 180.0f;
	//サインを求める
	float sin = sinf(radian);
	//コサインを求める
	float cos = cosf(radian);
	//単位行列にする
	Identity();
	//回転値の設定
	m[1][1] = m[2][2] = cos;
	m[1][2] = -sin;
	m[2][1] = sin;
}

const CVector3 CMatrix44::operator*(const CVector3 &v) const {
	return CVector3(
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]
		);
}

//移動行列を設定
void CMatrix44::SetTranslate(const CVector3 &v) {
	Identity();
	m[0][3] = v.x;
	m[1][3] = v.y;
	m[2][3] = v.z;
}

//*CMatrix44のオーバーロード
const CMatrix44 CMatrix44::operator*(const CMatrix44 &a) const {
	CMatrix44 r;
	for (int i = 0; i < 4; i++) {
		r.m[i][0] = m[i][0] * a.m[0][0] + m[i][1] * a.m[1][0] + m[i][2] * a.m[2][0] + m[i][3] * a.m[3][0];
		r.m[i][1] = m[i][0] * a.m[0][1] + m[i][1] * a.m[1][1] + m[i][2] * a.m[2][1] + m[i][3] * a.m[3][1];
		r.m[i][2] = m[i][0] * a.m[0][2] + m[i][1] * a.m[1][2] + m[i][2] * a.m[2][2] + m[i][3] * a.m[3][2];
		r.m[i][3] = m[i][0] * a.m[0][3] + m[i][1] * a.m[1][3] + m[i][2] * a.m[2][3] + m[i][3] * a.m[3][3];
	}
	return r;
}

