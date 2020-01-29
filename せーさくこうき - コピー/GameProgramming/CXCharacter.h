#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix44.h"

class CXCharacter{
public:
	CModelX*mpModel; //���f���f�[�^
	int mAnimationIndex; //�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg; //true�F�J��Ԃ�
	float mAnimationFrame; //�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize; //�A�j���[�V�����̍Đ��t���[����
	CVector3 mPosition; //�ʒu
	CVector3 mRotation; //��]�l
	CMatrix44 mMatrix; //�ʒu��]�s��


	//����������
	void Init(CModelX*model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	//�X�V����
	void Update(CMatrix44 &m);

	void Update();
	//�`�揈��
	void Render();
};

#endif