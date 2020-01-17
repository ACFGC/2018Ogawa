#ifndef C3DTRIANGLE_H
#define C3DTRIANGLE_H

#include "glut.h"
#include "CVector3.h"
#include "CMatrix44.h"

class C3DTriangle {
public:
	CVector3 mVertex[3];	//���_
	CVector3 mNormal;		//�@��
	//�s��
	CMatrix44 mMatrix;
	void Render() {
		CVector3 Vertex[3];
		CVector3 Normal;
		Vertex[0] = mMatrix * mVertex[0];
		Vertex[1] = mMatrix * mVertex[1];
		Vertex[2] = mMatrix * mVertex[2];
		//��]�s��ɂ���i�ړ���0�ɂ���j
		CMatrix44 nm = mMatrix;
		nm.m[0][3] = nm.m[1][3] = nm.m[2][3] = 0.0f;
		Normal = nm * mNormal;
		//�@���̐ݒ�
		glNormal3f(Normal.x, Normal.y, Normal.z);
		//�O�p�`�̕`��
		glBegin(GL_TRIANGLES);
		glVertex3f(Vertex[0].x, Vertex[0].y, Vertex[0].z);
		glVertex3f(Vertex[1].x, Vertex[1].y, Vertex[1].z);
		glVertex3f(Vertex[2].x, Vertex[2].y, Vertex[2].z);
		glEnd();
	}
};

#endif