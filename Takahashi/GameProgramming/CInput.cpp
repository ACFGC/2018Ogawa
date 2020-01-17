#include "CInput.h"
//ウィンドウポインタ 
GLFWwindow* CInput::mpWindow = 0;
/*
初期化 
Init(ウィンドウポインタ) 
*/ 
void CInput::Init(GLFWwindow* w) {
	mpWindow = w; 
} 
/*
マウスカーソルの座標を取得する 
ウィンドウの左上が原点(0,0) 
画面右方向がX軸プラス 
画面下方向がY軸プラス 
*/ 
void CInput::GetCursorPos(float *px, float *py) {
	double x, y; 
	glfwGetCursorPos(mpWindow, &x, &y); 
	*px = x; 
	*py = y; 
}
/* マウスボタンの状態 
GetMouseButton(ボタン) 
ボタン: 
GLFW_MOUSE_BUTTON_LEFT:左ボタン 
GLFW_MOUSE_BUTTON_RIGHT:右ボタン 
return: true：押されている 
false:押されていない 
*/ 
bool CInput::GetMouseButton(int button) { 
	int state = glfwGetMouseButton(mpWindow, button); 
	return state == GLFW_PRESS; 
}