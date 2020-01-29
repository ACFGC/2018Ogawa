#include "glut.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>
#include <string.h> //������֐��̃C���N���[�h

#include "CModelX.h"

void CModelX::Load(char*file){
	//
	//�t�@�C���T�C�Y���擾����
	//
	FILE *fp;	//�t�@�C���|�C���^�ϐ��̍쐬
	fp = fopen(file, "rb");	//�t�@�C�����I�[�v������
	if (fp == NULL) {	//�G���[�`�F�b�N
		printf("fopen error\n");
		return;
	}
	fseek(fp, 0L, SEEK_END);

	int size = ftell(fp);
	char *buf = mpPointer = new char[size + 1];	//�t�@�C���T�C�Y+1�o�C�g���̗̈���m��

	fseek(fp, 0L, SEEK_SET);
	fread(buf, size, 1, fp);	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	buf[size] = '\0';	//�Ō��\0��ݒ肷��i������̏I�[�j
	fclose(fp);	//�t�@�C�����N���[�Y����
	//
	//�t�@�C������3D���f���̃f�[�^��ǂݍ���
	//
	//FILE*fp;   //�t�@�C���|�C���^�ϐ��̍쐬
	//fp = fopen(file, "rb"); //�t�@�C�����I�[�v������
	//if (fp == NULL){ //�G���[�`�F�b�N
	//	printf("fopen error\n");
	//	return;
	//}
	////�t�@�C���T�C�Y+1�o�C�g���̗̈���m��
	//char*buf = mpPointer = new char[size + 1];
	////�m�ۂ����̈�Ƀt�@�C���T�C�Y���f�[�^��ǂݍ���
	//fread(buf, size, 1, fp);
	//buf[size] = '\0'; //�Ō��\0��ݒ肷��(������̏I�[)
	//fclose(fp); //�t�@�C�����N���[�Y����

	//printf(buf);

	//������̍Ō�܂ŌJ��Ԃ�
	while (*mpPointer != '\0'){
		GetToken(); //�P��̎擾
		//template �ǂݔ�΂�
		if (strcmp(mToken, "template") == 0){
			SkipNode();
		}
		//Material�̎�
		else if (strcmp(mToken, "Material") == 0){
			new CMaterial(this);
		}
		//�P�ꂪFrame�̏ꍇ
		else if (strcmp(mToken, "Frame") == 0){
			//�t���[�����쐬����
			new CModelXFrame(this);
		}
		//�P�ꂪAnimationSet�̏ꍇ
		else if (strcmp(mToken, "AnimationSet") == 0){
			new CAnimationSet(this);
		}
	}

	SAFE_DELETE_ARRAY(buf); //�m�ۂ����̈���������

	//�X�L���E�F�C�g�̃t���[���ԍ��ݒ�
	SetSkinWeightFrameIndex();
}

/*
GetToken
������f�[�^����A�P���1�擾����
*/
void CModelX::GetToken(){
	char*p = mpPointer;
	char*q = mToken;
	//��( )�^�u(\t)���s(\r)(\n)."�ȊO�̕����ɂȂ�܂œǂݔ�΂�
	while (*p != '\0'&& strchr(" \t\r\n,;\"", *p))p++;
	if (*p == '{' || *p == '}'){
		//�o�܂���}�Ȃ�mToken�ɑ�������̕�����
		*q++ = *p++;
	}
	else{
		//��( )�^�u(\r)(\n),;"}�̕����ɂȂ�܂�mToken�ɑ������
		while (*p != '\0'&& !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0'; //mToken�̍Ō�Ɂ��O����
	mpPointer = p; //���̓ǂݍ��݃|�C���g���X�V����
	//����mToken��//�̏ꍇ��,�R�����g�Ȃ̂ŉ��s�܂œǂݔ�΂�
	if (!strcmp("//", mToken)){
		//���s�܂œǂݔ�΂�
		while (*p != '\0'&& !strchr("\r\n", *p))p++;
		//�ǂݍ��݈ʒu�̍X�V
		mpPointer = p;
		//�P����擾����(�ċN�Ăяo��)
		GetToken();
	}
}

/*
SkipNode
�m�[�h��ǂݔ�΂�
*/
void CModelX::SkipNode(){
	//�������I�������I��
	while (*mpPointer != '\0'){
		GetToken(); //���̒P��擾
		//{�����������烋�[�v�I��
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	//�������I��邩�A�J�E���g��0�ɂȂ�����I��
	while (*mpPointer != '\0'&& count > 0){
		GetToken(); //���̒P��擾
		//{��������ƃJ�E���g�A�b�v
		if (strchr(mToken, '{'))count++;
		//}��������ƃJ�E���g�_�E��
		else if (strchr(mToken, '}'))count--;
	}
}

/*
CModelXFlame
model:CModelX�C���X�^���X�ւ̃|�C���^
�t���[�����쐬����
�ǂݍ��ݒ���Frame��������΁A�t���[�����쐬���A
�q�t���[���ɒǉ�����
*/
CModelXFrame::CModelXFrame(CModelX*model){
	//���݂̃t���[���z��̗v�f�����擾���ݒ肷��
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.Identity();
	//���̒P��(�t���[�����̗\��)���擾����
	model->GetToken(); //frame name
	//�t���[�������G���A���m�ۂ���
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[�������R�s�[����
	strcpy(mpName, model->mToken);
	//���̒P��({�̗\��)���擾����
	model->GetToken(); //{
	//�����������Ȃ�����I���
	while (*model->mpPointer != '\0'){
		//���̒P��擾
		model->GetToken();//Frame
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}'))break;
		//�V�ȃt���[���̏ꍇ�́A�q�t���[���ɒǉ�
		if (strcmp(model->mToken, "Frame") == 0){
			//�t���[�����쐬���A�q�t���[���̔z��ɒǉ�
			mChild.push_back(new CModelXFrame(model));
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0){
			model->GetToken(); //{
			for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++){
				mTransformMatrix.f[i] = model->GetFloatToken();
			}
			model->GetFloatToken(); //}
		}
		else if (strcmp(model->mToken, "Mesh") == 0){
			mMesh.Init(model);
		}
		else{
			//��L�ȊO�̗v�f�͓ǂݔ�΂�
			model->SkipNode();
		}
	}
	/*
	//�f�o�b�N�o�[�W�����̂ݗL��
	#ifdef _DEBUG
	printf("%s\n", mpName);
	for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.f); i++){
	printf(" %f", mTransformMatrix.f[i]);
	if (i % 4 == 3){
	printf("\n");
	}
	}
	#endif
	*/
}

/*
GetFloatToken
�P��𕂓������_�̃f�[�^�ŕԂ�
*/
float CModelX::GetFloatToken(){
	GetToken();
	//atof
	//�������float�^�֕ϊ�
	return atof(mToken);
}

/*
GetIntToken
�P��𐮐��̃f�[�^�ŕԂ�
*/
int CModelX::GetIntToken(){
	GetToken();
	return atoi(mToken);
}


/*
Init
Mesh�̃f�[�^����荞��
*/
void CMesh::Init(CModelX*model){
	model->GetToken(); //{ or ���O
	if (!strchr(model->mToken, '{')){
		//���O�̏ꍇ�A����{
		model->GetToken(); //{
	}
	//���_���̎擾
	mVertexNum = model->GetIntToken();
	//���_�����G���A�m��
	mpVertex = new CVector3[mVertexNum];
	mpAnimateVertex = new CVector3[mVertexNum];
	//���_�����f�[�^����荞��
	for (int i = 0; i < mVertexNum; i++){
		mpVertex[i].x = model->GetFloatToken();
		mpVertex[i].y = model->GetFloatToken();
		mpVertex[i].z = model->GetFloatToken();
	}
	mFaceNum = model->GetIntToken(); //�ʐ��ǂݍ���
	//���_���͈�ʂ�3���_
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3){
		model->GetToken(); //���_���ǂݔ�΂�
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	//�����������Ȃ�����I���
	while (model->mpPointer != '\0'){
		model->GetToken(); //MeshNormals
		//}�������̏ꍇ�͏I��
		if (strchr(model->mToken, '}'))
			break;
		if (strcmp(model->mToken, "MeshNormals") == 0){
			model->GetToken(); //{
			//�@���f�[�^�����擾
			mNormalNum = model->GetIntToken();
			//�@���̃f�[�^��z��Ɏ�荞��
			CVector3*pNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i++){
				pNormal[i].x = model->GetFloatToken();
				pNormal[i].y = model->GetFloatToken();
				pNormal[i].z = model->GetFloatToken();
			}
			//�@����=�ʐ�x3
			mNormalNum = model->GetIntToken() * 3; //FaceNum
			int ni;
			//���_���ɖ@���f�[�^��ݒ肷��
			mpNormal = new CVector3[mNormalNum];
			mpAnimateNormal = new CVector3[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3){
				model->GetToken(); //3
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 1] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[]pNormal;
			model->GetToken(); //}
		}
		else if (strcmp(model->mToken, "MeshMaterialList") == 0){
			model->GetToken(); //{
			//Material�̐�
			mMaterialNum = model->GetIntToken();
			//FaceNum
			mMaterialIndexNum = model->GetIntToken();
			//�}�e���A���C���f�b�N�X�̍쐬
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++){
				mpMaterialIndex[i] = model->GetIntToken();
			}
			//�}�e���A���f�[�^�̍쐬
			for (int i = 0; i < mMaterialNum; i++){
				model->GetToken(); //Material
				if (strcmp(model->mToken, "Material") == 0){
					mMaterial.push_back(new CMaterial(model));
				}
				else{
					//{���o
					model->GetToken(); //MaterialName
					mMaterial.push_back(model->FindMaterial(model->mToken));
					model->GetToken(); //}
				}
			}
			model->GetToken(); //}//End of MeshMaterialList
		}
		//SkinWeigfhts�̂Ƃ�
		else if (strcmp(model->mToken, "SkinWeights") == 0){
			//CSkinWeights�N���X�̃C���X�^���X���쐬���A�z��ɒǉ�
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		else if (strcmp(model->mToken, "MeshTextureCoords") == 0){
			model->GetToken();  //{
			//�e�N�X�`�����W�����擾
			int textureCoordsNum = model->GetIntToken();
			mpTextureCoords = new CVector2[textureCoordsNum];
			for (int i = 0; i < textureCoordsNum; i++){
				mpTextureCoords[i].x = model->GetFloatToken();
				mpTextureCoords[i].y = model->GetFloatToken();
			}
			model->GetToken(); //}
		}
		else{
			//�ȊO�̃m�[�h�͓ǂݔ�΂�
			model->SkipNode();
		}

		//�f�o�b�N�o�[�W�����̂ݗL��
#ifdef _DEBUG
		/*
		printf("NormalNum:%d", mNormalNum);
		for (int i = 0; i < mNormalNum; i++){
		if (i % 1 == 0){
		printf("\n");
		}
		printf("%10f", mpNormal[i].x);
		printf("%10f", mpNormal[i].y);
		printf("%10f", mpNormal[i].z);
		}
		*/
#endif
	}
}

void CMesh::Render(){
	/*���_�f�[�^�A�@���f�[�^�̔z���L���ɂ���*/
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	/*���_�f�[�^�A�@���f�[�^�̔z����w�肷��*/
	glVertexPointer(3, GL_FLOAT, 0, mpAnimateVertex);
	glNormalPointer(GL_FLOAT, 0, mpAnimateNormal);
	glTexCoordPointer(2, GL_FLOAT, 0, mpTextureCoords);

	/*���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷��*/
	//	glDrawElements(GL_TRIANGLES, 3 * mFaceNum, GL_UNSIGNED_INT, mpVertexIndex);


	/*���_�̃C���f�b�N�X�̏ꏊ���w�肵�Đ}�`��`�悷��*/
	for (int i = 0; i < mFaceNum; i++){
		//�}�e���A����K�p����
		mMaterial[mpMaterialIndex[i]]->SetMaterial();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
		//�}�e���A������������
		mMaterial[mpMaterialIndex[i]]->UnSetMaterial();
	}

	/*���_�f�[�^�A�@���f�[�^�̔z��𖳌��ɂ���*/
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

/*
AnimateVertex
���_�ɃA�j���[�V������K�p
*/
void CMesh::AnimateVertex(CModelX*model){
	//�A�j���[�V�����p�̒��_�G���A�N���A
	memset(mpAnimateVertex, 0, sizeof(CVector3)*mVertexNum);
	memset(mpAnimateNormal, 0, sizeof(CVector3)*mNormalNum);
	//�X�L���E�F�C�g���J��Ԃ�
	for (int i = 0; i < mSkinWeights.size(); i++){
		//�t���[���ԍ��擾
		int frameIndex = mSkinWeights[i]->mFrameIndex;
		//�t���[�������s��ɃI�t�Z�b�g�s�������
		CMatrix44 mSkinningMatrix = mSkinWeights[i]->mOffset * model->mFrame[frameIndex]->mCombinedMatrix;
		//���_�����J��Ԃ�
		for (int j = 0; j < mSkinWeights[i]->mIndexNum; j++){
			//���_�ԍ��擾
			int index = mSkinWeights[i]->mpIndex[j];
			//�d�ݎ擾
			float weight = mSkinWeights[i]->mpWeight[j];
			//���_�Ɩ@�����X�V����
			mpAnimateVertex[index] += mpVertex[index] * mSkinningMatrix*weight;
			mpAnimateNormal[index] += mpNormal[index] * mSkinningMatrix*weight;
		}
	}
	//�@���𐳋K������
	for (int i = 0; i < mNormalNum; i++){
		mpAnimateNormal[i] = mpAnimateNormal[i].normalize();
	}
}

/*
Render
���b�V���̖ʐ���0�ȏ�Ȃ�`�悷��
*/
void CModelXFrame::Render(){
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}

/*
Render
�S�Ẵt���[���̕`�揈�����Ăяo��
*/
void CModelX::Render(){
	for (int i = 0; i < mFrame.size(); i++){
		mFrame[i]->Render();
	}
}

/*
SetMaterial
�}�e���A����K�p����
*/
void CMaterial::SetMaterial(){
	glMaterialfv(GL_FRONT, GL_EMISSION, mEmissive);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &mPower);
	//�e�N�X�`�����L��ꍇ
	if (mTextureID > 0){
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h����
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		//�e�N�X�`���}�b�s���O�̃f�[�^��L���ɂ���
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*
UnSetMaterial
�e�N�X�`���}�b�s���O�𖳌��ɂ���
*/
void CMaterial::UnSetMaterial(){
	//�e�N�X�`�����L��ꍇ
	if (mTextureID > 0){
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`���𖳌��ɂ���
		glDisable(GL_TEXTURE_2D);
		//�e�N�X�`���}�b�s���O�̃f�[�^�𖳌��ɂ���
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}

/*
Material�f�[�^�̓ǂݍ��݂Ɛݒ�
*/
CMaterial::CMaterial(CModelX*model)
:mpName(0)
, mpTextureFilename(0)
, mTextureID(0)
{
	//CModelX�Ƀ}�e���Al��ǉ�����
	model->mMaterial.push_back(this);
	model->GetToken(); //{?Name
	if (strcmp(model->mToken, "{") != 0){
		//{�łȂ��Ƃ��̓}�e���A����
		mpName = new char[strlen(model->mToken) + 1];
		strcpy(mpName, model->mToken);
		model->GetToken(); //{
	}
	mDiffuse[0] = model->GetFloatToken();
	mDiffuse[1] = model->GetFloatToken();
	mDiffuse[2] = model->GetFloatToken();
	mDiffuse[3] = model->GetFloatToken();

	mPower = model->GetFloatToken();

	mSpecular[0] = model->GetFloatToken();
	mSpecular[1] = model->GetFloatToken();
	mSpecular[2] = model->GetFloatToken();

	mEmissive[0] = model->GetFloatToken();
	mEmissive[1] = model->GetFloatToken();
	mEmissive[2] = model->GetFloatToken();

	model->GetToken(); //TextureFilename or }

	if (strcmp(model->mToken, "TextureFilename") == 0){
		//�e�N�X�`������̏ꍇ�A�e�N�X�`���t�@�C�����擾
		model->GetToken(); //{
		model->GetToken(); //filename
		mpTextureFilename = new char[strlen(model->mToken) + 1];
		strcpy(mpTextureFilename, model->mToken);
		//�e�N�X�`���t�@�C�����Ńe�N�X�`������������
		CTexture*p = model->FindTexture(model->mToken);
		//�e�N�X�`�����݂鎞
		if (p){
			//�e�N�X�`��ID���擾
			mTextureID = p->mId;
		}
		else{
			//�����ꍇ�A�e�N�X�`���ǂݍ���
			p = new CTexture(model->mToken);
			if (p->mpName){
				//�e�N�X�`���z��ɒǉ�
				model->mTexture.push_back(p);
				//�e�N�X�`��ID���擾
				mTextureID = p->mId;
			}
		}
		model->GetToken(); //}
		model->GetToken(); //}
	}
	/*
	#ifdef _DEBUG
	printf("%s\n", mpName);
	printf("mDiffuse:");
	printf("%10f ", mDiffuse[0]);
	printf("%10f ", mDiffuse[1]);
	printf("%10f ", mDiffuse[2]);
	printf("%10f\n", mDiffuse[3]);
	printf("mPower:");
	printf("%10f\n", mPower);
	printf("mSpecular:");
	printf("%10f ", mSpecular[0]);
	printf("%10f ", mSpecular[1]);
	printf("%10f ", mSpecular[2]);
	printf("%10f\n", mSpecular[3]);
	printf("mEmissive:");
	printf("%10f ", mEmissive[0]);
	printf("%10f ", mEmissive[1]);
	printf("%10f ", mEmissive[2]);
	printf("%10f\n", mEmissive[3]);
	#endif
	*/
}

/*
FindMaterial
�}�e���A�����ɊY������}�e���A����ԋp����
*/
CMaterial*CModelX::FindMaterial(char*name){
	//�}�e���A���z��̃C�e���[�^�쐬
	std::vector <CMaterial*>::iterator itr;
	//�}�e���A���z���擪���珇�Ɍ���
	for (itr = mMaterial.begin(); itr != mMaterial.end(); itr++){
		//���O����v����΃}�e���A���̃|�C���^��ԋp
		if (strcmp(name, (*itr)->mpName) == 0){
			return*itr;
		}
	}
	//�����Ƃ���NULL��ԋp
	return NULL;
}

/*
FindTexture
name�ɊY������t�@�C���������e�N�X�`�����������ĕԋp����
*/
CTexture*CModelX::FindTexture(char*name){
	//�e�N�X�`���z��̃C�e���[�^�쐬
	std::vector<CTexture*>::iterator itr;
	//�e�N�X�`���z��̐擪���珇�Ɍ���
	for (itr = mTexture.begin(); itr != mTexture.end(); itr++){
		//���O����v����΃e�N�X�`���̃|�C���^��ԋp
		if (strcmp(name, (*itr)->mpName) == 0){
			return *itr;
		}
	}
	//�����Ƃ���NULL��ԋp
	return NULL;
}


/*
CSkinWeights
�X�L���E�F�C�g�̓ǂݍ���
*/
CSkinWeights::CSkinWeights(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mIndexNum(0)
, mpIndex(0)
, mpWeight(0)
{
	model->GetToken(); //{
	model->GetToken(); //FrameName
	//�t���[�����G���A�m�ہA�ݒ�
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//���_�ԍ����擾
	mIndexNum = model->GetIntToken();
	//���_�ԍ�����0�𒴂���
	if (mIndexNum > 0){
		//���_�ԍ��ƒ��_�E�F�C�g�̃G���A�m��
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//���_�ԍ��擾
		for (int i = 0; i < mIndexNum; i++)
			mpIndex[i] = model->GetIntToken();
		//���_�E�F�C�g�擾
		for (int i = 0; i < mIndexNum; i++)
			mpWeight[i] = model->GetFloatToken();
	}
	//�I�t�Z�b�g�s��擾
	for (int i = 0; i < 16; i++){
		mOffset.f[i] = model->GetFloatToken();
	}
	model->GetToken(); //}
#ifdef _DEBUG
	/*
	printf("SkinWeights %s\n", mpFrameName);
	if (mIndexNum > 0){
	for (int i = 0; i < mIndexNum; i++){
	printf("%d ", mpIndex[i]);
	printf("%f\n", mpWeight[i]);
	}
	}
	for (int i = 0; i < 16; i++){
	printf("%9f ", mOffset.f[i]);
	if (i % 4 == 3){
	printf("\n");
	}
	}
	*/
#endif
}

/*
CAnimationSet
*/
CAnimationSet::CAnimationSet(CModelX*model)
:mpName(0)
, mTime(0)
, mWeight(0)
, mMaxTime(0)
{
	model->mAnimationSet.push_back(this);
	model->GetToken(); //Animation Name
	//�A�j���[�V�����̖��O��ޔ�
	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken(); //{
	while (*model->mpPointer != '\0'){
		model->GetToken(); //}orAnimation
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Animation") == 0){
			//Animation�v�f�ǂݍ���
			mAnimation.push_back(new CAnimation(model));
		}
	}
	//�I�����Ԑݒ�
	mMaxTime = mAnimation[0]->mpKey[mAnimation[0]->mKeyNum - 1].mTime;
#ifdef _DEBUG
	//printf("AnimationSet:%s\n", mpName);
#endif
}

CAnimation::CAnimation(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mKeyNum(0)
, mpKey(0)
{
	model->GetToken(); //{ or Animation Name
	if (strchr(model->mToken, '{')){
		model->GetToken(); //{
	}
	else{
		model->GetToken(); //{
		model->GetToken(); //{
	}

	model->GetToken(); //FrameName
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex =
		model->FindFrame(model->mToken)->mIndex;
	model->GetToken(); //}
	//�L�[�̔z���ۑ����Ă����z��
	CMatrix44*Key[4] = { 0, 0, 0, 0 };
	//���Ԃ̔z���ۑ����Ă����z��
	float*time[4] = { 0, 0, 0, 0 };
	while (*model->mpPointer != '\0'){
		model->GetToken(); //} or AnimationKey
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "AnimationKey") == 0){
			model->GetToken(); //{
			//�f�[�^�̃^�C�v�擾
			int type = model->GetIntToken();
			//���Ԑ��擾
			mKeyNum = model->GetIntToken();
			switch (type){
			case 0: //Rotation Quaternion
				//�s��̔z������Ԑ����m��
				Key[type] = new CMatrix44[mKeyNum];
				//���Ԃ̔z������Ԑ����m��
				time[type] = new float[mKeyNum];
				//���Ԑ����J��Ԃ�
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken(); //4��ǂݔ�΂�
					//w,x,y,z���擾
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					//�N�H�[�^�j�I�������]�s��ɕϊ�
					Key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1: //�g��E�k���̍s��쐬
				Key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken(); //3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					Key[type][i].m00 = x;
					Key[type][i].m11 = y;
					Key[type][i].m22 = z;
				}
				break;
			case 2: //�ړ��̍s��쐬
				Key[type] = new CMatrix44[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken(); //3
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					CVector3 vec(x, y, z);
					Key[type][i].SetTranslate(vec);

				}
				break;
			case 4: //�s��f�[�^�̎擾
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					mpKey[i].mTime = model->GetFloatToken(); //Time
					model->GetToken(); //16
					for (int j = 0; j < 16; j++){
						mpKey[i].mMatrix.f[j] = model->GetFloatToken();
					}
				}
				break;
			}
			model->GetToken(); //}
		}
		else{
			model->SkipNode();
		}
	} //While�̏I���
	//�s��f�[�^�ł͂Ȃ���
	if (mpKey == 0){
		//���Ԑ����L�[���쐬
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0; i<mKeyNum; i++){
			//���Ԑݒ�
			mpKey[i].mTime = time[2][i]; //Time
			//�s��쐬 Position*Rotation*Size
			mpKey[i].mMatrix = Key[1][i] * Key[0][i] * Key[2][i];
		}
	}
	//�m�ۂ����G���A���
	for (int i = 0; i < ARRAY_SIZE(Key); i++){
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(Key[i]);
	}
	/*
	#ifdef _DEBUG
	printf("Animation:%s\n", mpFrameName);
	for (int i = 0; i < 16; i++){
	printf("%9f ", mpKey[0].mMatrix.f[i]);

	if (i % 4 == 3){
	printf("\n");
	}
	}
	#endif
	*/
}

/*
AnimationFrame
�t���[���̕ϊ��s����A�j���[�V�����f�[�^�ōX�V����
*/
void CModelX::AnimateFrame(){
	//�A�j���[�V�����œK�p�����t���[���̕ϊ��s����[���N���A�ɂ���
	for (int i = 0; i<mAnimationSet.size(); i++){
		CAnimationSet*anim = mAnimationSet[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0)continue;
		//�t���[����(Animation��)�J��Ԃ�
		for (int j = 0; j<anim->mAnimation.size(); j++){
			CAnimation*animation = anim->mAnimation[j];
			//�Y������t���[���̕ϊ��s����[���N���A����
			memset(&mFrame[animation->mFrameIndex]->mTransformMatrix, 0, sizeof(CMatrix44));
		}
	}
	//�A�j���[�V�����ɊY������t���[���̕ϊ��s����A�j���[�V�����̃f�[�^�Őݒ肷��
	for (int i = 0; i < mAnimationSet.size(); i++){
		CAnimationSet*anim = mAnimationSet[i];
		//�d�݂�0�͔�΂�
		if (anim->mWeight == 0)continue;
		//�t���[����(Animation��)�J��Ԃ�
		for (int j = 0; j < anim->mAnimation.size(); j++){
			//�t���[�����擾����
			CAnimation*animation = anim->mAnimation[j];
			CModelXFrame*frame = mFrame[animation->mFrameIndex];
			//�L�[�������ꍇ�͔�΂�
			if (animation->mpKey == 0)continue;
			//���Ԃ��擾
			float time = anim->mTime;
			//�ŏ��̎��Ԃ�菬�����ꍇ
			if (time < animation->mpKey[0].mTime){
				//�ϊ��s���0�R�}�ڂ̍s��ōX�V
				frame->mTransformMatrix += animation->mpKey[0].mMatrix*anim->mWeight;
			}
			//�Ō�̎��Ԃ��傫���ꍇ
			else if (time >= animation->mpKey[animation->mKeyNum - 1].mTime){
				//�ϊ��s����Ō�̃R�}�̍s��ōX�V
				frame->mTransformMatrix += animation->mpKey[animation->mKeyNum - 1].mMatrix*anim->mWeight;
			}
			else{
				//���Ԃ̓r���̏ꍇ
				for (int k = 1; k < animation->mKeyNum; k++){
					//�ϊ��s����A���`��ԂɂčX�V
					if (time < animation->mpKey[k].mTime &&  animation->mpKey[k - 1].mTime != animation->mpKey[k].mTime){
						float r = (animation->mpKey[k].mTime - time) / (animation->mpKey[k].mTime - animation->mpKey[k - 1].mTime);
						frame->mTransformMatrix += (animation->mpKey[k - 1].mMatrix*r + animation->mpKey[k].mMatrix*(1 - r))*anim->mWeight;
						break;
					}
				}
			}
		}
	}
#ifdef _DEBUG
	/*
	for (int i = 0; i < mFrame.size(); i++){
	printf("Frame:%s\n", mFrame[i]->mpName);
	for (int j = 0; j < 16; j++){
	printf("%9f ", mFrame[i]->mTransformMatrix.f[j]);
	if (j % 4 == 3)
	printf("\n");
	}
	}
	*/
#endif
}

/*
AnimateVertex
���_�ɃA�j���[�V������K�p����
*/
void CModelX::AnimateVertex(){
	//�t���[�������J��Ԃ�
	for (int i = 0; i < mFrame.size(); i++){
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum>0){
			//���_���A�j���[�V�����ōX�V����
			mFrame[i]->mMesh.AnimateVertex(this);
		}
	}
}



/*
AnimateCombined
�����s��̍쐬
*/
void CModelXFrame::AnimateCombined(CMatrix44*parent){
	//�e����̕ϊ��s��ɁA�����̕ϊ��s����|����
	mCombinedMatrix = mTransformMatrix * (*parent);
	//�q�t���[���̍����s����쐬����
	for (int i = 0; i < mChild.size(); i++){
		mChild[i]->AnimateCombined(&mCombinedMatrix);
	}
}

/*
SetSkinWeightFrameIndex
�X�L���E�F�C�g�̃t���[���ԍ���ݒ肷��
*/
void CModelX::SetSkinWeightFrameIndex(){
	//�t���[�������J��Ԃ�
	for (int i = 0; i < mFrame.size(); i++){
		//���b�V���ɖʂ������
		if (mFrame[i]->mMesh.mFaceNum>0){
			//�X�L���E�F�C�g���J��Ԃ�
			for (int j = 0; j < mFrame[i]->mMesh.mSkinWeights.size(); j++){
				//�t���[�����̃t���[�����擾����
				CModelXFrame*frame = FindFrame(mFrame[i]->mMesh.mSkinWeights[j]->mpFrameName);
				//�t���[���ԍ���ݒ肷��
				mFrame[i]->mMesh.mSkinWeights[j]->mFrameIndex = frame->mIndex;
			}
		}
	}
}

