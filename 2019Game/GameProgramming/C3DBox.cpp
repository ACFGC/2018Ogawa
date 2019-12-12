#include "C3DBox.h"

void C3DBox::SetWHD(float w, float h, float d) {
	this->w = w; this->h = h; this->d = d;
	//Z+��
	mTriangle[0].mVertex[0].x = -w;
	mTriangle[0].mVertex[0].y = -h;
	mTriangle[0].mVertex[0].z = d;
	mTriangle[0].mVertex[1].x = w;
	mTriangle[0].mVertex[1].y = -h;
	mTriangle[0].mVertex[1].z = d;
	mTriangle[0].mVertex[2].x = w;
	mTriangle[0].mVertex[2].y = h;
	mTriangle[0].mVertex[2].z = d;
	mTriangle[0].mNormal = CVector3(0.0f, 0.0f, 1.0f);
	mTriangle[1].mVertex[0].x = -w;
	mTriangle[1].mVertex[0].y = h;
	mTriangle[1].mVertex[0].z = d;
	mTriangle[1].mVertex[1].x = -w;
	mTriangle[1].mVertex[1].y = -h;
	mTriangle[1].mVertex[1].z = d;
	mTriangle[1].mVertex[2].x = w;
	mTriangle[1].mVertex[2].y = h;
	mTriangle[1].mVertex[2].z = d;
	mTriangle[1].mNormal = CVector3(0.0f, 0.0f, 1.0f);
	//X+��
	mTriangle[2].mVertex[0].x = w;
	mTriangle[2].mVertex[0].y = -h;
	mTriangle[2].mVertex[0].z = d;
	mTriangle[2].mVertex[1].x = w;
	mTriangle[2].mVertex[1].y = -h;
	mTriangle[2].mVertex[1].z = -d;
	mTriangle[2].mVertex[2].x = w;
	mTriangle[2].mVertex[2].y = h;
	mTriangle[2].mVertex[2].z = -d;
	mTriangle[2].mNormal = CVector3(1.0f, 0.0f, 0.0f);
	mTriangle[3].mVertex[0].x = w;
	mTriangle[3].mVertex[0].y = h;
	mTriangle[3].mVertex[0].z = d;
	mTriangle[3].mVertex[1].x = w;
	mTriangle[3].mVertex[1].y = -h;
	mTriangle[3].mVertex[1].z = d;
	mTriangle[3].mVertex[2].x = w;
	mTriangle[3].mVertex[2].y = h;
	mTriangle[3].mVertex[2].z = -d;
	mTriangle[3].mNormal = CVector3(1.0f, 0.0f, 0.0f);
	//Y+��
	mTriangle[4].mVertex[0].x = -w;
	mTriangle[4].mVertex[0].y = h;
	mTriangle[4].mVertex[0].z = d;
	mTriangle[4].mVertex[1].x = w;
	mTriangle[4].mVertex[1].y = h;
	mTriangle[4].mVertex[1].z = d;
	mTriangle[4].mVertex[2].x = w;
	mTriangle[4].mVertex[2].y = h;
	mTriangle[4].mVertex[2].z = -d;
	mTriangle[4].mNormal = CVector3(0.0f, 1.0f, 0.0f);
	mTriangle[5].mVertex[0].x = -w;
	mTriangle[5].mVertex[0].y = h;
	mTriangle[5].mVertex[0].z = d;
	mTriangle[5].mVertex[1].x = w;
	mTriangle[5].mVertex[1].y = h;
	mTriangle[5].mVertex[1].z = -d;
	mTriangle[5].mVertex[2].x = -w;
	mTriangle[5].mVertex[2].y = h;
	mTriangle[5].mVertex[2].z = -d;
	mTriangle[5].mNormal = CVector3(0.0f, 1.0f, 0.0f);
	//Z-��
	mTriangle[6].mVertex[1].x = -w;
	mTriangle[6].mVertex[1].y = -h;
	mTriangle[6].mVertex[1].z = -d;
	mTriangle[6].mVertex[0].x = w;
	mTriangle[6].mVertex[0].y = -h;
	mTriangle[6].mVertex[0].z = -d;
	mTriangle[6].mVertex[2].x = w;
	mTriangle[6].mVertex[2].y = h;
	mTriangle[6].mVertex[2].z = -d;
	mTriangle[6].mNormal = CVector3(0.0f, 0.0f, -1.0f);
	mTriangle[7].mVertex[1].x = -w;
	mTriangle[7].mVertex[1].y = h;
	mTriangle[7].mVertex[1].z = -d;
	mTriangle[7].mVertex[0].x = -w;
	mTriangle[7].mVertex[0].y = -h;
	mTriangle[7].mVertex[0].z = -d;
	mTriangle[7].mVertex[2].x = w;
	mTriangle[7].mVertex[2].y = h;
	mTriangle[7].mVertex[2].z = -d;
	mTriangle[7].mNormal = CVector3(0.0f, 0.0f, -1.0f);
	//X-��
	mTriangle[8].mVertex[1].x = -w;
	mTriangle[8].mVertex[1].y = -h;
	mTriangle[8].mVertex[1].z = d;
	mTriangle[8].mVertex[0].x = -w;
	mTriangle[8].mVertex[0].y = -h;
	mTriangle[8].mVertex[0].z = -d;
	mTriangle[8].mVertex[2].x = -w;
	mTriangle[8].mVertex[2].y = h;
	mTriangle[8].mVertex[2].z = -d;
	mTriangle[8].mNormal = CVector3(-1.0f, 0.0f, 0.0f);
	mTriangle[9].mVertex[1].x = -w;
	mTriangle[9].mVertex[1].y = h;
	mTriangle[9].mVertex[1].z = d;
	mTriangle[9].mVertex[0].x = -w;
	mTriangle[9].mVertex[0].y = -h;
	mTriangle[9].mVertex[0].z = d;
	mTriangle[9].mVertex[2].x = -w;
	mTriangle[9].mVertex[2].y = h;
	mTriangle[9].mVertex[2].z = -d;
	mTriangle[9].mNormal = CVector3(-1.0f, 0.0f, 0.0f);

	//Y-��
	mTriangle[10].mVertex[0].x = -w;
	mTriangle[10].mVertex[0].y = -h;
	mTriangle[10].mVertex[0].z =  d;
	mTriangle[10].mVertex[1].x =  w;
	mTriangle[10].mVertex[1].y = -h;
	mTriangle[10].mVertex[1].z = -d;
	mTriangle[10].mVertex[2].x =  w;
	mTriangle[10].mVertex[2].y = -h;
	mTriangle[10].mVertex[2].z =  d;
	mTriangle[10].mNormal = CVector3(0.0f, -1.0f, 0.0f);
	mTriangle[11].mVertex[0].x = -w;
	mTriangle[11].mVertex[0].y = -h;
	mTriangle[11].mVertex[0].z =  d;
	mTriangle[11].mVertex[1].x = -w;
	mTriangle[11].mVertex[1].y = -h;
	mTriangle[11].mVertex[1].z = -d;
	mTriangle[11].mVertex[2].x =  w;
	mTriangle[11].mVertex[2].y = -h;
	mTriangle[11].mVertex[2].z = -d;
	mTriangle[11].mNormal = CVector3(0.0f, -1.0f, 0.0f);
}

void C3DBox::Render() {
	//�g�U���i�f�B�t���[�Y�j�F�̐ݒ�
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	mTriangle[0].Render();
	mTriangle[1].Render();
	mTriangle[2].Render();
	mTriangle[3].Render();
	mTriangle[4].Render();
	mTriangle[5].Render();
	mTriangle[6].Render();
	mTriangle[7].Render();
	mTriangle[8].Render();
	mTriangle[9].Render();
	mTriangle[10].Render();
	mTriangle[11].Render();
}

void C3DBox::Update() {
	//��]�s��̐ݒ�
	mMatrixRotation.SetRotationY(mRotation.y);
	//X����]�s��̍쐬
	CMatrix44 rx;
	rx.SetRotationX(mRotation.x);
	//X���ŉ�]���Ă���Y���ŉ�]������
	mMatrixRotation = mMatrixRotation * rx;
	//�i�s�����̐ݒ�
	mForward = mMatrixRotation * CVector3(0.0f, 0.0f, 1.0f);
	//�ړ��s��̐ݒ�
	mMatrixTranslate.SetTranslate(mPosition);
	//�e�O�p�`�̉�]�s��ɐݒ�
	mMatrix = 
	mTriangle[0].mMatrix = 
	mTriangle[1].mMatrix = 
	mTriangle[2].mMatrix = 
	mTriangle[3].mMatrix = 
	mTriangle[4].mMatrix = 
	mTriangle[5].mMatrix = 
	mTriangle[6].mMatrix = 
	mTriangle[7].mMatrix = 
	mTriangle[8].mMatrix =
	mTriangle[10].mMatrix =
	mTriangle[11].mMatrix =
	mTriangle[12].mMatrix =
	mTriangle[13].mMatrix =
	mTriangle[9].mMatrix = mMatrixTranslate * mMatrixRotation;

	
}

//�O�i����
void C3DBox::Forward() {
	mPosition = mPosition + mForward * mVelocity;
}


//��]����
void C3DBox::LeftTurn(){
	mRotation.y = mRotation.y += 1.0f;
}

void C3DBox::RightTurn(){
	mRotation.y = mRotation.y -= 1.0f;
}

//�g�U���̐ݒ�
void C3DBox::SetDiffuse(float r, float g, float b, float a) {
	mDiffuse[0] = r;
	mDiffuse[1] = g;
	mDiffuse[2] = b;
	mDiffuse[3] = a;
}
