#ifndef CMATRIX44_H
#define CMATRIX44_H

#include "CVector3.h"

class CMatrix44 {
public:
	//4x4の2次元配列
	float m[4][4];
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
};

#endif
