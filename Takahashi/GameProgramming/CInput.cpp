#include "CInput.h"
//�E�B���h�E�|�C���^ 
GLFWwindow* CInput::mpWindow = 0;
/*
������ 
Init(�E�B���h�E�|�C���^) 
*/ 
void CInput::Init(GLFWwindow* w) {
	mpWindow = w; 
} 
/*
�}�E�X�J�[�\���̍��W���擾���� 
�E�B���h�E�̍��オ���_(0,0) 
��ʉE������X���v���X 
��ʉ�������Y���v���X 
*/ 
void CInput::GetCursorPos(float *px, float *py) {
	double x, y; 
	glfwGetCursorPos(mpWindow, &x, &y); 
	*px = x; 
	*py = y; 
}
/* �}�E�X�{�^���̏�� 
GetMouseButton(�{�^��) 
�{�^��: 
GLFW_MOUSE_BUTTON_LEFT:���{�^�� 
GLFW_MOUSE_BUTTON_RIGHT:�E�{�^�� 
return: true�F������Ă��� 
false:������Ă��Ȃ� 
*/ 
bool CInput::GetMouseButton(int button) { 
	int state = glfwGetMouseButton(mpWindow, button); 
	return state == GLFW_PRESS; 
}