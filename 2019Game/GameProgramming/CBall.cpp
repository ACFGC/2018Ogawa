#include "CBall.h"
#include "CRectangle.h"
#include "CTexture.h"


void CBall::Init(){
	/*
	SetVertex(-20.0f, 20.0f, -24.0f, 24.0f);
	mBoxCollider.mSize.x = 20.0f;
	mBoxCollider.mSize.y = 24.0f;
	mBoxCollider.mpTask = this;
	*/
}


void CBall::Update(){
	CRectangle::Update();

	CMatrix33 rot;
	rot.SetRotation(mRotation);
	mForward = rot.MultiVector2(CVector2(0.0f, 1.0f));
	mBackward = rot.MultiVector2(CVector2(0.0f, -1.0f));
}


void CBall::LeftTurn(){
	mRotation = mRotation + 1;
}


void CBall::RightTurn(){
	mRotation = mRotation - 1;
}

void CBall::Forward(){
	//mPosition.x = mPosition.x + mForward.x;
	//mPosition.y = mPosition.y + mForward.y;
	mPosition = mPosition + mForward;
}

void CBall::Backward(){
	//mPosition.x = mPosition.x + mBackward.x;
	//mPosition.y = mPosition.y + mBackward.y;
	mPosition = mPosition - mForward;
}

void CBall::Render(){
	CRectangle::Render();
}
