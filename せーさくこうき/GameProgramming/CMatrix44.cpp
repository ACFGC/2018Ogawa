#include "CMatrix44.h"
#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード


CMatrix44::CMatrix44() {
	identity();	//単位行列に設定
}

/* 単位行列の設定
| 1 0 0 0 |
| 0 1 0 0 |
| 0 0 1 0 |
| 0 0 0 1 |
*/
void CMatrix44::identity() {
	for (int i = 0; i < 16; i++) {
		f[i] = 0.0f;
	}
	m00 = m11 = m22 = m33 = 1.0f;
}
/* Y軸回転行列の設定
| cos 0 -sin 0 |
|  0  1   0  0 |
| sin 0  cos 0 |
|  0  0   0  1 |
*/
void CMatrix44::rotationY(float deg) {
	float r = deg * M_PI / 180.0f;
	m[0][0] = cos(r);
	m[2][2] = cos(r);
	m[2][0] = sin(r);
	m[0][2] = -sin(r);
}
/* X軸回転行列の設定
| 1   0    0   0 |
| 0  cos  sin  0 |
| 0 -sin  cos  0 |
| 0   0    0   1 |
*/
void CMatrix44::rotationX(float deg) {
	float r = deg * M_PI / 180.0f;
	m[1][1] = cos(r);
	m[2][2] = cos(r);
	m[2][1] = -sin(r);
	m[1][2] = sin(r);
}
/* 移動行列の設定
| 1 0 0 0 |
| 0 1 0 0 |
| 0 0 1 0 |
| x y z 1 |
*/
void CMatrix44::translate(float pos[3]) {
	m[3][0] = pos[0];
	m[3][1] = pos[1];
	m[3][2] = pos[2];
}
/* 頂点との掛け算
| x y z 1 | * | a b c d |
| e f g h |
| i j k l |
| m n o p |
x = x*a + y*e + z*i + 1*m
y = x*b + y*f + z*j + 1*n
z = x*c + y*g + z*k + 1*o
*/
void CMatrix44::multi(float *x, float *y, float *z) {
	float a = *x, b = *y, c = *z;
	*x = a * m[0][0] + b * m[1][0] + c * m[2][0] + 1.0f * m[3][0];
	*y = a * m[0][1] + b * m[1][1] + c * m[2][1] + 1.0f * m[3][1];
	*z = a * m[0][2] + b * m[1][2] + c * m[2][2] + 1.0f * m[3][2];
}
//行列同士の掛け算
const CMatrix44 CMatrix44::operator * (const CMatrix44 &r) const {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp.m[i][j] = 0.0f;
			for (int k = 0; k < 4; k++) {
				tmp.m[i][j] += r.m[i][k] * m[k][j];
			}
		}
	}
	return tmp;
}

/* ベクトルから移動行列を作成する
v：ベクトル｜x,y,z｜
*/
void CMatrix44::translate(CVector4 v) {
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}

void CMatrix44::translate(CVector3 v) {
	m[3][0] = v.x;
	m[3][1] = v.y;
	m[3][2] = v.z;
}


void CMatrix44::SetQuaternion(float x, float y, float z, float w) {
	m00 = 1 - 2 * y*y - 2 * z*z;	m01 = 2 * x*y + 2 * w*z;		m02 = 2 * x*z - 2 * w*y;		m03 = 0;
	m10 = 2 * x*y - 2 * w*z;		m11 = 1 - 2 * x*x - 2 * z*z;	m12 = 2 * y*z + 2 * w*x;		m13 = 0;
	m20 = 2 * x*z + 2 * w*y;		m21 = 2 * y*z - 2 * w*x;		m22 = 1 - 2 * x*x - 2 * y*y;	m23 = 0;
	m30 = 0;						m31 = 0;						m32 = 0;						m33 = 1;
}

//行列同士の掛け算
const CMatrix44 CMatrix44::operator * (float f) const {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmp.m[i][j] = m[i][j] * f;
		}
	}
	return tmp;
}

void CMatrix44::operator += (const CMatrix44 &r) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] += r.m[i][j];
		}
	}
}

const CMatrix44 CMatrix44::operator + (const CMatrix44 &r) const {
	CMatrix44 tmp;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
				tmp.m[i][j] = r.m[i][j] + m[i][j];
		}
	}
	return tmp;
}
