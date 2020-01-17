#ifndef CTEXTURE_H
#define CTEXTURE_H
#include "glut.h"
/*
TGA�t�@�C���̃w�b�_�t�H�[�}�b�g
*/
struct STgaheader {
	unsigned char	dummy1[12];
	unsigned short	width;	//��
	unsigned short	height;	//����
	unsigned char	depth;	//�r�b�g�̐[��
	unsigned char	dummy2;
};
/*
�e�N�X�`���[�N���X
*/
class CTexture {
public:
	//�e�N�X�`��ID
	GLuint mId;
	//TGA�t�@�C���̃w�b�_���
	STgaheader header;
	//�t�@�C����
	char* mpName;
	/*
	�f�t�H���g�R���X�g���N�^
	*/
	CTexture() : mId(0)
		, mpName(0)
	{}
	/*
	�f�X�g���N�^�i���̃C���X�^���X���j�������Ƃ��Ɏ��s�����j
	*/
	~CTexture() {
		//�e�N�X�`���f�[�^������΍폜����
		if (mId != 0) {
			//�e�N�X�`���f�[�^�̍폜
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
	�摜�t�@�C���̓ǂݍ��݁i�e�N�X�`���t�@�C���̓ǂݍ��݁j
	*/
	void Load(const char* filename);

	void DrawImage(int left, int right, int bottom, int top, float fLeft, float tRight, float tBottom, float tTop);
};

#endif
