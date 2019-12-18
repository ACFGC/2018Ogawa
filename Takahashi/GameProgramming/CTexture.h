#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"
/*
TGAファイルのヘッダフォーマット
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;	//幅
	unsigned short	height;	//高さ
	unsigned char	depth;	//ビットの深さ
	unsigned char	dummy2;
};
/*
テクスチャークラス
*/
class CTexture {
public:
	//テクスチャID
	GLuint mId;
	//TGAファイルのヘッダ情報
	STgaheader header;
	//ファイル名
	char* mpName;
	/*
	デフォルトコンストラクタ
	*/
	CTexture() : mId(0)
		, mpName(0)
	{}
	/*
	デストラクタ（このインスタンスが破棄されるときに実行される）
	*/
	~CTexture() {
		//テクスチャデータがあれば削除する
		if (mId != 0) {
			//テクスチャデータの削除
			glDeleteTextures(1, &mId);
			mId = 0;
		}
		if (mpName) {
			delete[] mpName;
			mpName = 0;
		}
	}
	CTexture(char *file)
		: mId(0)
		, mpName(0) {
		Load(file);
	}


	/*
	画像ファイルの読み込み（テクスチャファイルの読み込み）
	*/
	void Load(const char* filename);

	void DrawImage(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop);
};

#endif
