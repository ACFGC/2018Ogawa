#ifndef CMATRIX44_H
#define CMATRIX44_H

#include "CVector3.h"

class CMatrix44 {
public:
	//4x4の2次元配列
	float m[4][4];
	union //共用体 共通の領域を参照する
	{
		float	f[16];
		float	m[4][4];
		struct
		{
			float	m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33;
		};
	};
	//コンストラクタ
	CMatrix44() {
		Identity();
	}
	//単位行列に設定
	void Identity();
	//Y軸を中心に回転
	void SetRotationY(float degree);
	//X軸を中心に回転
	void SetRotationX(float degree);
	//行列の表示
	void Print();
	//*CVector3のオーバーロード
	const CVector3 operator*(const CVector3 &v) const;
	//移動行列を設定
	void SetTranslate(const CVector3 &v);
	//*CMatrix44のオーバーロード
	const CMatrix44 operator*(const CMatrix44 &m) const;
	
	void SetQuaternion(float x, float y, float z, float w);
	const CMatrix44 operator * (float f) const;
	const CMatrix44 operator + (const CMatrix44 &r) const;
	void CMatrix44::operator += (const CMatrix44 &r);
	CMatrix44 CMatrix44::Transpose() const;

};

#endif
