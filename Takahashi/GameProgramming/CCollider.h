#ifndef CCOLLIDER_H
#define CCOLLIDER_H

//�^�X�N�N���X�̐錾
class CTask;
//���R���C�_�̐錾
class CSphereCollider;
//3�����x�N�g���̃C���N���[�h
#include "CVector3.h"
#include "CMatrix44.h"

class C3DCollider;

/*
�ՓˊǗ��N���X�̒�`
*/
class CCollisionManager {
private:
	//private�̃����o�́A�����̃N���X�����A�N�Z�X�ł���
	//�C���X�^���X�̃|�C���^
	static CCollisionManager *mpInstance;
	//�擪�|�C���^
	C3DCollider *mpHead;
	//�ŏI�|�C���^
	C3DCollider *mpTail;

	CCollisionManager()
		: mpHead(0)
		, mpTail(0)
	{}
public:
	//public�̃����o�́A�S�ẴN���X����A�N�Z�X�ł���
	//�C���X�^���X�̎擾
	static CCollisionManager* Get();
	//�R���C�_�����X�g�֒ǉ�����
	void Add(C3DCollider *p);
	//�Փˏ���
	void Update();
	//�j������
	void Destroy();
	//���ڃ��X�g����폜����
	void Remove(C3DCollider*);
};


/*
 3D�p�̃R���C�_�N���X
*/
class C3DCollider {
public:
	//�R���C�_�̌^
	enum EColTag{
		E3DBOX,
		ESPHERE,
	};
	EColTag mTag;
	//���L��
	CTask *mpTask;
	//�ϊ��s��
	CMatrix44 *mpMatrix;
	//���S���W
	CVector3 mPosition;
	//�����f�[�^
	CVector3 mAdjust;
	//���|�C���^
	C3DCollider *mpNext;
	//�O�|�C���^
	C3DCollider *mpPrev;
	//�R���X�g���N�^
	C3DCollider()
		: mpNext(0)
		, mpPrev(0)
	{
		//���X�g�ɒǉ�
		CCollisionManager::Get()->Add(this);
	}
	//�f�X�g���N�^
	virtual ~C3DCollider() {
		//���X�g����폜
		CCollisionManager::Get()->Remove(this);
	}
	//�Փ˔��菈��
	virtual bool Collision(CSphereCollider *p, int*px, int*py, int*pz) { return false; };
	static bool Collision(C3DCollider*, C3DCollider*);
	virtual bool Collision(CSphereCollider *p) { return false; };
};
/*
 ���R���C�_�N���X
*/
class CSphereCollider : public C3DCollider {
public:
	//���a
	float mRadius;
	CSphereCollider()
	{
		//���R���C�_�ݒ�
		mTag = ESPHERE;
	}
	//�Փ˔��菈��
//	bool Collision(CSphereCollider *p, int*px, int*py, int*pz);
	bool CSphereCollider::Collision(CSphereCollider *p2);
};
/*
 �����̃R���C�_�N���X
*/
class C3DBoxCollider : public C3DCollider {
public:
	//�����̂̑傫�� x:�� y:���� z:���s
	CVector3 mSize;
	C3DBoxCollider()
	{
		//�l�p�`�R���C�_�ݒ�
		mTag = E3DBOX;
	}
	//�����̂Ƌ��̏Փ˔���
//	bool Collision(CSphereCollider *p, int*px, int*py, int*pz);
	bool C3DBoxCollider::Collision(CSphereCollider *p);
};



#endif
