#ifndef CSCENE_H
#define CSCENE_H

#include "CText.h"

#include "CXCharacter.h"

/*
�V�[���̊�{�N���X
*/
class CScene {
public:
	//?
	CXCharacter mXPlayer;
	CModelX mModelX;

	static CScene *spInstance;
	//�V�[���̎��ʒl
	enum ESceneTag {
		EROOT,
		EGAME,	//�Q�[���V�[��
		EWIN,	//����
		ELOSE	//�s�k
	};
	//�V�[���̎��ʎq
	ESceneTag mSceneTag;

	
	CText mText;

	//���z�֐�
	//�f�X�g���N�^�����z�֐��ɂ��Ȃ���
	//�q�N���X�̃f�X�g���N�^���Ă΂�Ȃ�
	virtual ~CScene() {}
	virtual void Init();
	virtual void Update();
};

#endif
