#include "CTexture.h"

/*
文字の描画
*/
class CText {
public:
	//テクスチャの指定
	static CTexture mFont;
	CText() {
		if (mFont.mId == 0) {
			mFont.Load("font.tga");
		}
	}
	//文字の描画
	static void DrawChar(char ch, int x, int y, int w, int h);
	//
	static void DrawString(char *s, int x, int y, int w, int h);
};
