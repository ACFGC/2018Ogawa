#ifndef CBALL_H
#define CBALL_H

#include"CRectangle.h"
#include"C3DBox.h"
#include<stdio.h>


class CBall :public CRectangle{
public:
	void Init();
	void Update();
	void LeftTurn();
	void RightTurn();

	CVector2 mForward;
	CVector2 mBackward;

	void Forward();
	void Backward();

	void Render();

	CSphereCollider mColSphere;
	void OnCollision(C3DCollider *i, C3DCollider *y);
};

#endif