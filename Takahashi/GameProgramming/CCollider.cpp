#include "CCollider.h"
#include "CTask.h"
//?
#include "glut.h"
#include "C3DBox.h"

//�C���X�^���X��static�ϐ�
CCollisionManager* CCollisionManager::mpInstance = 0;
//�C���X�^���X�̎擾
CCollisionManager* CCollisionManager::Get() {
	//�C���X�^���X������(0)�̎�
	if (mpInstance == 0) {
		//�C���X�^���X���쐬���đ��
		mpInstance = new CCollisionManager();
	}
	//�C���X�^���X�̃|�C���^��Ԃ�
	return mpInstance;
}
//���X�g�֒ǉ�
void CCollisionManager::Add(C3DCollider *p) {
	if (mpHead == 0) {
		//���X�g�̍ŏ�
		//���X�g�̐擪�ɂ���
		mpHead = p;
		mpHead->mpPrev = 0;
		//���X�g�̍Ō�ɂ���
		mpTail = p;
		//�Ō�̎��͖����ɂ���
		mpTail->mpNext = 0;
	}
	else {
		//�Ō�ɒǉ�
		mpTail->mpNext = p;
		p->mpPrev = mpTail;
		mpTail = p;
		p->mpNext = 0;
	}
}

//�j������
void CCollisionManager::Destroy() {
	//���X�g�̃R���C�_��col�ŎQ�Ƃ��Ă���
	C3DCollider *col = mpHead;
	//col��0�ɂȂ�����I��
	while (col) {
		//���̃|�C���^��ޔ�
		C3DCollider *next = col->mpNext;
		//���ڂ��폜
		delete col;
		//���̃��X�g��
		col = next;
	}
	//�Ō��������
	mpTail = 0;
	//�ՓˊǗ��̃C���X�^���X�폜
	delete mpInstance;
	//�C���X�^���X�ւ̃|�C���^������
	mpInstance = 0;
}

void CCollisionManager::Remove(C3DCollider* p) {
	if (p == mpHead) {
		mpHead = p->mpNext;
		if (mpHead)
			mpHead->mpPrev = 0;
	}
	else if (p == mpTail) {
		mpTail = p->mpPrev;
		if (mpTail)
			mpTail->mpNext = 0;
	}
	else {
		p->mpPrev->mpNext = p->mpNext;
		p->mpNext->mpPrev = p->mpPrev;
	}
}

//���Ƌ��̏Փ˔���
bool CSphereCollider::Collision(CSphereCollider *p2) {
	//�R���C�_�̒��S���W���ړ������܂�
	CVector3 pos1 = *mpMatrix * mPosition;
	CVector3 pos2 = *p2->mpMatrix * p2->mPosition;
	//���S�ƒ��S�̃x�N�g�������߂܂�
//	pos1 = pos1 - pos2;
	//pos1:����@pos2:����
	pos1 = pos2 - pos1;
	//�x�N�g���̒����Ɣ��a�̑傫�����r���܂�
	if (pos1.Length() < mRadius + p2->mRadius) {
		//�Փ˂��Ă���
		mAdjust = pos1 * ((mRadius + p2->mRadius - pos1.Length()) / (mRadius + p2->mRadius));
		p2->mAdjust = mAdjust * -1;
		return true;
	}
	else {
		//�Փ˂��Ă��Ȃ�
		mAdjust = p2->mAdjust = CVector3(0.0f, 0.0f, 0.0f);
	}
	return false;
}
//�����̂Ƌ��̏Փ˔���
bool C3DBoxCollider::Collision(CSphereCollider *p) {
	//�����̂̒��S���W�����߂�
	CVector3 center = *mpMatrix * mPosition;
	//�����̂�X�����������߂�
//	CVector3 vx = *mpMatrix * (CVector3(1.0f, 0.0f, 0.0f) + mPosition) - center;
	CVector3 vx = *mpMatrix * CVector3(1.0f, 0.0f, 0.0f) - *mpMatrix * CVector3(0.0f, 0.0f, 0.0f);
	//�����̂�Y�����������߂�
//	CVector3 vy = *mpMatrix * (CVector3(0.0f, 1.0f, 0.0f) + mPosition) - center;
	CVector3 vy = *mpMatrix * CVector3(0.0f, 1.0f, 0.0f) - *mpMatrix * CVector3(0.0f, 0.0f, 0.0f);
	//�����̂�Z�����������߂�
//	CVector3 vz = *mpMatrix * (CVector3(0.0f, 0.0f, 1.0f) + mPosition) - center;
	CVector3 vz = *mpMatrix * CVector3(0.0f, 0.0f, 1.0f) - *mpMatrix * CVector3(0.0f, 0.0f, 0.0f);
	//�����̂��狅�ւ̃x�N�g�������߂�
	CVector3 vBS = *p->mpMatrix*p->mPosition - center;
	//�����̂��狅�ցA�����̂�X���ɑ΂��钷���Ƃ̍������߂�
	float dx = p->mRadius + mSize.x - fabs(vx.Dot(vBS));
	//�����̂��狅�ցA�����̂�Y���ɑ΂��钷���Ƃ̍������߂�
	float dy = p->mRadius + mSize.y - fabs(vy.Dot(vBS));
	//�����̂��狅�ցA�����̂�Z���ɑ΂��钷���Ƃ̍������߂�
	float dz = p->mRadius + mSize.z - fabs(vz.Dot(vBS));
	//�Փ˂��Ă��邩���肷��
	if (dx > 0.0f && dy > 0.0f && dz > 0.0f) {
		//�߂��ʂ��ŏ��̎��Ŗ߂�
		if (dx > dy) {
			if (dy > dz) {
				//Z���Ŗ߂� ��Adjust�F�߂��l
				if (vz.Dot(vBS) > 0.0f) {
					//+����
					mAdjust = vz * dz;
				}
				else {
					//-����
					mAdjust =  vz * -dz;
				}
			}
			else {
				//Y���Ŗ߂�
				if (vy.Dot(vBS) > 0.0f) {
					mAdjust = vy * dy;
				}
				else {
					mAdjust = vy * -dy;
				}
			}
		}
		else {
			if (dx > dz) {
				//Z���Ŗ߂�
				if (vz.Dot(vBS) > 0.0f) {
					mAdjust = vz * dz;
				}
				else {
					mAdjust = vz * -dz;
				}
			}
			else {
				//X���Ŗ߂�
				if (vx.Dot(vBS) > 0.0f) {
					mAdjust = vx * dx;
				}
				else {
					mAdjust = vx * -dx;
				}
			}
		}
		p->mAdjust = mAdjust * -1.0f;
		return true;
	}
	return false;
}
//�R���C�_�̏Փ˔���
void CCollisionManager::Update() {
	C3DCollider *col1 = mpHead;
	while (col1 != 0) {
		//col1����col1�ȍ~�̏Փ˂𔻒肷��
		for (C3DCollider *col2 = col1->mpNext; col2 != 0; col2 = col2->mpNext) {
			if (col1->mpTask != col2->mpTask) {
				col1->mpTask->OnCollision(col1, col2);
				col2->mpTask->OnCollision(col2, col1);
			}
		}
		//���̃R���C�_��
		col1 = col1->mpNext;
	}
}

void CCollisionManager::Render() {
	C3DCollider *col1 = mpHead;
	while (col1 != 0) {
		col1->Render();
		//���̃R���C�_��
		col1 = col1->mpNext;
	}
}



bool C3DCollider::Collision(C3DCollider* i, C3DCollider*y) {
	switch (i->mTag) {
	case E3DBOX:
		switch (y->mTag) {
		case ESPHERE:
			return ((C3DBoxCollider*)i)->Collision((CSphereCollider*)y);
			break;
		}
		break;
	case ESPHERE:
		switch (y->mTag) {
		case ESPHERE:
			return ((CSphereCollider*)i)->Collision((CSphereCollider*)y);
			break;
		case E3DBOX:
			return ((C3DBoxCollider*)y)->Collision((CSphereCollider*)i);
			break;
		}
		break;
	}
	return false;
}

void C3DBoxCollider::Render() {
	return;
	glPushMatrix();
	glMultMatrixf(mpMatrix->Transpose().m[0]);
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	C3DBox box;
	box.SetWHD(mSize.x, mSize.y, mSize.z);
	box.Render();

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}

void CSphereCollider::Render() {
	glPushMatrix();
	glMultMatrixf(mpMatrix->Transpose().m[0]);
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	glutWireSphere(mRadius, 16, 16);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glPopMatrix();

}


