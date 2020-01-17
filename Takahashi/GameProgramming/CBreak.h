#ifndef CBREAK_H
#define CBREAK_H

#include "CCharacter.h"
/*
������Ə�����u���b�N�̃N���X
*/
class CBreak : public CCharacter {
public:
	CBreak(float x, float y, float z, float w, float h, float d, float rx, float ry, float rz)
		//�e�̃N���X��������
		: CCharacter(x, y, z, w, h, d, rx, ry, rz)
	{}
	//�Փˏ���
	void OnCollision(C3DCollider *i, C3DCollider *y) {
		//�Փ˔�����Ă�
		if (C3DCollider::Collision(i, y)) {
			CPlayer::spInstance->mVelocity.y = 0.5;
			//�Փ˂��Ă����疳���ɂ���
			mEnabled = false;
		}
	}
};


#endif
