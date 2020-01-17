#ifndef CINPUT_H 
#define CINPUT_H

#include "GLFW/glfw3.h" 
/* ���̓N���X CInput */ 
class CInput { 
	//�E�B���h�E�|�C���^ 
	static GLFWwindow* mpWindow; 
public:
/* 
������ 
Init(�E�B���h�E�|�C���^) 
*/ 
	static void Init(GLFWwindow* w); 
	/* 
	�}�E�X�J�[�\���̍��W���擾���� 
	GetCursorPos(X���W�|�C���^,Y���W�|�C���^) 
	*/ 
	static void GetCursorPos(float *px, float *py); 
	/* 
	�}�E�X�{�^���̏�� 
	GetMouseButton(�{�^��) 
	�{�^��: 
	GLFW_MOUSE_BUTTON_LEFT:���{�^�� 
	GLFW_MOUSE_BUTTON_RIGHT:�E�{�^�� 
	return: 
	true�F������Ă��� 
	false:������Ă��Ȃ� */ 
	static bool GetMouseButton(int button);
}; 

#endif