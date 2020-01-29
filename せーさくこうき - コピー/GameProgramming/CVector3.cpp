#include"CVector3.h"


const CVector3 CVector3::operator + (const CVector3 &v) const {
	return CVector3(x + v.x, y + v.y, z + v.z);
}