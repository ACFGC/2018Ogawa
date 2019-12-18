#include "CVector3.h"
#include "CMatrix44.h"

const CVector3 CVector3::operator * (const CMatrix44 &m) const {
	CVector3 tmp;
//	CMatrix44 r = m.Transpose();
	CMatrix44 r = m;
	tmp.x = x * r.m[0][0] + y * r.m[1][0] + z * r.m[2][0] + 1.0f * r.m[3][0];
	tmp.y = x * r.m[0][1] + y * r.m[1][1] + z * r.m[2][1] + 1.0f * r.m[3][1];
	tmp.z = x * r.m[0][2] + y * r.m[1][2] + z * r.m[2][2] + 1.0f * r.m[3][2];
	return tmp;
}
