#include <stdio.h>	//ファイルの入力に使用
#include "CTexture.h"
#include <string.h>

void CTexture::Load(const char* filename) {
	//画像データ
	unsigned char* data;
	//ファイルポインタの作成
	FILE *fp;
	//ファイルオープン
	fp = fopen(filename, "rb");
	//エラーのときはリターン
	if (fp == 0) {
			printf("file not found:%s\n", filename);
		return;
	}
	//ヘッダ情報を読み込む
	fread(&header, sizeof(header), 1, fp);
	//画像データのバイト数を計算する
	int length = header.width * header.height * header.depth / 8;
	//画像データの格納領域を確保
	data = new unsigned char[length];
	//画像データをヘッダの続きから読み込む
	fread(data, length, 1, fp);
	//画像ファイルのクローズ
	fclose(fp);

	//テクスチャデータの登録
	glGenTextures(1, &mId);
	glBindTexture(GL_TEXTURE_2D, mId);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	if (header.depth == 32)
		//アルファ有りのテクスチャ作成
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, header.width,
		header.height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);
	else
		//アルファ無しのテクスチャ作成
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, header.width,
		header.height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	//格納領域を解放
	delete[] data;

	mpName = new char[strlen(filename) + 1];
	strcpy(mpName, filename);


}

void CTexture::DrawImage(int left, int right, int bottom, int top, float tleft, float tright, float tbottom, float ttop) {
	//テクスチャを有効にする
	glEnable(GL_TEXTURE_2D);
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//テクスチャを指定
	glBindTexture(GL_TEXTURE_2D, mId);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(tleft / header.width, (header.height - ttop) / header.height);
	glVertex2d(left, top);
	glTexCoord2f(tleft / header.width, (header.height - tbottom) / header.height);
	glVertex2d(left, bottom);
	glTexCoord2f(tright / header.width, (header.height - tbottom) / header.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tleft / header.width, (header.height - ttop) / header.height);
	glVertex2d(left, top);
	glTexCoord2f(tright / header.width, (header.height - tbottom) / header.height);
	glVertex2d(right, bottom);
	glTexCoord2f(tright / header.width, (header.height - ttop) / header.height);
	glVertex2d(right, top);
	glEnd();

	//テクスチャを解放
	glBindTexture(GL_TEXTURE_2D, 0);
	//アルファブレンドを無効
	glDisable(GL_BLEND);
	//テクスチャを無効
	glDisable(GL_TEXTURE_2D);
}
