#include"CRectangle.h"
#include"GLFW/glfw3.h"

void CRectangle::SetVertex(float left, float right, float bottom, float top){
	mVertex[0].x = left; mVertex[0].y = bottom;
	mVertex[1].x = right; mVertex[1].y = bottom;
	mVertex[2].x = right; mVertex[2].y = top;
	mVertex[3].x = left; mVertex[3].y = top;
}

void CRectangle::Update(){
	CMatrix33 rot, sca;
	mMatrix.SetTranslate(mPosition.x, mPosition.y);
	rot.SetRotation(mRotation);
	sca.SetScale(mScale.x, mScale.y);
	mMatrix = mMatrix*rot*sca;
}

void CRectangle::Render(){
	CVector2 v[4];
	v[0] = mMatrix*mVertex[0];
	v[1] = mMatrix*mVertex[1];
	v[2] = mMatrix*mVertex[2];
	v[3] = mMatrix*mVertex[3];

	glColor4fv(mColor);

	if (mpTexture == 0){
		glBegin(GL_QUADS);
		glVertex2d(v[0].x, v[0].y);
		glVertex2d(v[1].x, v[1].y);
		glVertex2d(v[2].x, v[2].y);
		glVertex2d(v[3].x, v[3].y);
		glEnd();
	}
	else{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, mpTexture->mId);
		glBegin(GL_QUADS);
		glTexCoord2f(mUv[0].x, mUv[0].y);
		glVertex2d(v[0].x, v[0].y);
		glTexCoord2f(mUv[1].x, mUv[1].y);
		glVertex2d(v[1].x, v[1].y);
		glTexCoord2f(mUv[2].x, mUv[2].y);
		glVertex2d(v[2].x, v[2].y);
		glTexCoord2f(mUv[3].x, mUv[3].y);
		glVertex2d(v[3].x, v[3].y);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
}

void CRectangle::SetColor(float r, float g, float b, float a)
{
	mColor[0] = r; mColor[1] = g;
	mColor[2] = b; mColor[3] = a;

}

void CRectangle::SetTexture(CTexture*t, float left, float right, float bottom, float top){
	mpTexture = t;
	mUv[0].x = left / t->header.width;
	mUv[0].y = (t->header.height - bottom) / t->header.height;
	mUv[1].x = right / t->header.width;
	mUv[1].y = (t->header.height - bottom) / t->header.height;
	mUv[2].x = right / t->header.width;
	mUv[2].y = (t->header.height - top) / t->header.height;
	mUv[3].x = left / t->header.width;
	mUv[3].y = (t->header.height - top) / t->header.height;
}