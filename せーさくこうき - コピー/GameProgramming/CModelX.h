#ifndef CMODELX_H //�C���N���[�h�K�[�h
#define CMODELX_H

#define MODEL_FILE "���O�i.x" //���̓t�@�C����
//�z��̃T�C�Y�擾���}�N����
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))

//�̈�J�����}�N����
#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}

#include <vector>�@//vectot�N���X�̃C���N���[�h(���I�z��)
#include "CMatrix44.h" //�}�g���N�X�N���X�̃C���N���[�h
#include "CTexture.h"
#include "CVector2.h"
class CModelX; //CModelX�N���X�̐錾

/*
CMaterial
�}�e���A���N���X
*/
class CMaterial{
public:
	char*mpName; //�}�e���A����
	float mDiffuse[4];
	float mPower;
	float mSpecular[3];
	float mEmissive[3];
	//�e�N�X�`��ID
	GLuint mTextureID;
	//�e�N�X�`���t�@�C����
	char*mpTextureFilename;

	CMaterial(CModelX*model);


	~CMaterial(){
		SAFE_DELETE_ARRAY(mpName);
		SAFE_DELETE_ARRAY(mpTextureFilename);
	}
	void SetMaterial();
	void UnSetMaterial();
};

/*
CSkinWeights
�X�L���E�F�C�g�N���X
*/
class CSkinWeights{
public:
	char*mpFrameName; //�t���[����
	int mFrameIndex; //�t���[���ԍ�
	int mIndexNum; //���_�ԍ���
	int *mpIndex; //���_�ԍ��z��
	float *mpWeight; //���_�E�F�C�g�z��
	CMatrix44 mOffset; //�I�t�Z�b�g�}�g���b�N�X

	CSkinWeights(CModelX*model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);
	}
};

/*
CAnimationKey
�A�j���[�V�����L�[�N���X
*/
class CAnimationKey{
public:
	//����
	float mTime;
	//�s��
	CMatrix44 mMatrix;
};

/*
CAnimation
�A�j���[�V����
*/
class CAnimation{
public:
	char*mpFrameName; //�t���[����
	int mFrameIndex; //�t���[���ԍ�
	int mKeyNum; //�L�[��(���Ԑ�)
	CAnimationKey*mpKey; //�L�[�̔z��

	CAnimation(CModelX*model);

	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
	}
};

/*
CAnimationSet
�A�j���[�V�����Z�b�g
*/
class CAnimationSet{
public:
	//�A�j���[�V������
	char*mpName;

	float mTime; //���ݎ���
	float mWeight; //�d��
	float mMaxTime; //�ő厞��

	CAnimationSet(CModelX*model);

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
	}

	std::vector<CAnimation*>mAnimation;
};


//CMesh�N���X�̒�`
class CMesh{
public:
	int mVertexNum; //���_��
	CVector3*mpVertex; //���_�f�[�^
	int mFaceNum; //�ʐ�
	int *mpVertexIndex; //�ʂ��\�����钸�_�ԍ�
	int mNormalNum; //�@����
	CVector3*mpNormal; //�@���f�[�^
	int mMaterialNum; //�}�e���A����
	int mMaterialIndexNum; //�}�e���A���ԍ���(�ʐ�)
	int *mpMaterialIndex; //�}�e���A���ԍ�
	CVector3*mpAnimateVertex; //�A�j���[�V�����p���_
	CVector3*mpAnimateNormal; //�A�j���[�V�����p�@��
	CVector2*mpTextureCoords; //�e�N�X�`�����W�f�[�^


	std::vector<CMaterial*>mMaterial; //�}�e���A���f�[�^
	//�X�L���E�F�C�g
	std::vector<CSkinWeights*>mSkinWeights;

	//�R���X�g���N�^
	CMesh()
		:mVertexNum(0)
		, mpVertex(0)
		, mFaceNum(0)
		, mpVertexIndex(0)
		, mNormalNum(0)
		, mpNormal(0)
		, mMaterialNum(0)
		, mMaterialIndexNum(0)
		, mpMaterialIndex(0)
		, mpAnimateVertex(0)
		, mpAnimateNormal(0)
		, mpTextureCoords(0)
	{}
	//�f�X�g���N�^
	~CMesh(){
		SAFE_DELETE_ARRAY(mpVertex);
		SAFE_DELETE_ARRAY(mpVertexIndex);
		SAFE_DELETE_ARRAY(mpNormal);
		SAFE_DELETE_ARRAY(mpMaterialIndex);
		SAFE_DELETE_ARRAY(mpAnimateVertex);
		SAFE_DELETE_ARRAY(mpAnimateNormal);
		SAFE_DELETE_ARRAY(mpTextureCoords);
		//�X�L���E�F�C�g�̍폜
		for (int i = 0; i < mSkinWeights.size(); i++){
			delete mSkinWeights[i];
		}
	}
	//�ǂݍ��ݏ���
	void Init(CModelX*model);
	void Render();
	void AnimateVertex(CModelX*model);
};

//CModelXFrame�N���X�̒�`
class CModelXFrame{
public:
	std::vector<CModelXFrame*>mChild; //�q�t���[���̔z��
	CMatrix44 mTransformMatrix; //�ϊ��s��
	CMatrix44 mCombinedMatrix; //�����s��
	CMesh mMesh; //Mesh�f�[�^
	char*mpName; //�t���[�����O
	int mIndex;  //�t���[���ԍ�
	//�R���X�g���N�^
	CModelXFrame(CModelX*model);
	//�f�X�g���N�^
	~CModelXFrame(){
		//�q�t���[����S�ĊJ������
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete*itr;
		}
		//���O�̃G���A���������
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
	//�����s��̍쐬
	void AnimateCombined(CMatrix44*parent);
};

/*
CModelX
X�t�@�C���`����3D���f���f�[�^���v���O�����ŔF������
*/
class CModelX{
public:
	char*mpPointer;     //�ǂݎ��ʒu
	char mToken[1024];  //���o�����P��̗̈�
	std::vector<CModelXFrame*>mFrame; //�t���[���̔z��
	std::vector<CAnimationSet*>mAnimationSet; //�A�j���[�V�����Z�b�g�̔z��
	std::vector<CMaterial*>mMaterial; //�}�e���A���̔z��]
	std::vector<CTexture*>mTexture; //�e�N�X�`���̔z��

	//���������_�f�[�^�̎擾
	float GetFloatToken();
	//�����f�[�^�̎擾
	int GetIntToken();
	/*
	�P��𐮐��^�̃f�[�^�ŕԂ�
	*/

	CModelX()
		:mpPointer(0)
	{}

	~CModelX(){
		delete mFrame[0];
		for (int i = 0; i < mAnimationSet.size(); i++){
			delete mAnimationSet[i];
		}
		for (int i = 0; i < mMaterial.size(); i++){
			delete mMaterial[i];
		}
		//�e�N�X�`���̉��
		for (int i = 0; i < mTexture.size(); i++){
			delete mTexture[i];
		}
	}
	//�t�@�C���ǂݍ���
	void Load(char*file);
	//�P��̎��o��
	void GetToken();
	//�m�[�h�̓ǂݔ�΂�
	void SkipNode();
	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	void SetSkinWeightFrameIndex();
	//���_�ɃA�j���[�V������K�p
	void AnimateVertex();

	void Render();

	void AnimateFrame();

	CMaterial*FindMaterial(char*name);
	//�e�N�X�`���̌���
	CTexture*FindTexture(char*name);

	/*
	FindFrame
	�t���[�����ɊY������t���[���̃A�h���X��Ԃ�
	*/
	CModelXFrame*CModelX::FindFrame(char*name){
		//�C�e���[�^�̍쐬
		std::vector<CModelXFrame*>::iterator itr;
		//�퓬����Ō�܂ŌJ��Ԃ�
		for (itr = mFrame.begin(); itr != mFrame.end(); itr++){
			//���O����v������?
			if (strcmp(name, (*itr)->mpName) == 0){
				//��v�����炻�̃A�h���X��Ԃ�
				return *itr;
			}
		}
		//��v����t���[�������ꍇ��NULL��Ԃ�
		return NULL;
	}
};


#endif