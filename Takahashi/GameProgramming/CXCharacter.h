#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix44.h"
//�R���C�_�N���X�̐錾
class CCollider;

class CXCharacter {
public:
	//�L�����N�^�[�̎���
	enum ECharTag {
		EPLAYER = 1, //1���珇��
		EENEMY,
	};
	ECharTag mTag;	//�L�����N�^���ʃ^�O

	CModelX *mpModel;	//���f���f�[�^
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�J��Ԃ�
	float mAnimationFrame; //�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize;//�A�j���[�V�����̍Đ��t���[����
	CVector3 mPosition;	//�ʒu
	CVector3 mRotation;	//��]�l
	CMatrix44 mMatrix;	//�ʒu��]�s��
	float mVelocityG; //�d�͑��x

	//����������
	void Init(CModelX *model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix44 &m);
	void Update();
	//�`�揈��
	void Render();
	//�Փˏ���
	virtual bool Collision(CCollider*, CCollider*){
		return false;
	};
	// �d�͏���
	void Gravity();


};

#endif

