#include"CVector3.h"
#include "CMatrix44.h"


const CVector3 CVector3::operator * (const CMatrix44 &m) const {
	CVector3 tmp;
	tmp.x = x * m.m[0][0] + y * m.m[1][0] + z * m.m[2][0] + 1.0f * m.m[3][0];
	tmp.y = x * m.m[0][1] + y * m.m[1][1] + z * m.m[2][1] + 1.0f * m.m[3][1];
	tmp.z = x * m.m[0][2] + y * m.m[1][2] + z * m.m[2][2] + 1.0f * m.m[3][2];
	return tmp;
}
void CVector3::operator += (const CVector3 &v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

CVector3 CVector3::normalize() {
	float len = Length();
	return CVector3(x / len, y / len, z / len);
}