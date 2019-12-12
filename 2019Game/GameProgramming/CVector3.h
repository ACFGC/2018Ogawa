#ifndef CVECTOR3_H
#define CVECTOR3_H

#define _USE_MATH_DEFINES	//数学ライブラリのM_PIを有効にする
#include <math.h>	//数学ライブラリのインクルード

/*
 3Dベクトルクラス
*/
class CVector3 {
public:
	//3D座標
	float x;
	float y;
	float z;
	//デフォルトコンストラクタ
	CVector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}
	//引数付きコンストラクタ
	CVector3(float ix, float iy, float iz)
		: x(ix), y(iy), z(iz)
	{}

	//*floatのオーバーロード
	const CVector3 operator*(float f) const {
		return CVector3(x*f, y*f, z*f);
	}
	//+CVector3のオーバーロード
	const CVector3 operator+(const CVector3 &v) const {
		return CVector3(x + v.x, y + v.y, z + v.z);
	}
	//-CVector3のオーバーロード
	const CVector3 operator-(const CVector3 &v) const {
		return CVector3(x - v.x, y - v.y, z - v.z);
	}
	/*
	 長さを求める
	*/
	float CVector3::Length() {
		return sqrtf(x*x + y*y + z*z);
	}
	/*
	 ベクトル値からx軸y軸の回転角度を求める
	 atan2(y, x) -180°～180°
	*/
	CVector3 CVector3::GetRotation() {
		CVector3 rot;
		//Y軸の回転角度
		rot.y = -(atan2f(z, x)) * 180.0f / M_PI;
		//X軸の回転角度
//		rot.x = -(atan2f(y, Length())) * 180.0f / M_PI;
		rot.x = -(atan2f(y, sqrtf(x*x+z*z))) * 180.0f / M_PI;
		return rot;
	}
	/*
	 内積を求める
	*/
	float CVector3::Dot(const CVector3 &v) {
		return x * v.x + y * v.y + z * v.z;
	}

};


#endif
