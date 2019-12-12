#ifndef CINPUT_H 
#define CINPUT_H

#include "GLFW/glfw3.h" 
/* 入力クラス CInput */ 
class CInput { 
	//ウィンドウポインタ 
	static GLFWwindow* mpWindow; 
public:
/* 
初期化 
Init(ウィンドウポインタ) 
*/ 
	static void Init(GLFWwindow* w); 
	/* 
	マウスカーソルの座標を取得する 
	GetCursorPos(X座標ポインタ,Y座標ポインタ) 
	*/ 
	static void GetCursorPos(float *px, float *py); 
	/* 
	マウスボタンの状態 
	GetMouseButton(ボタン) 
	ボタン: 
	GLFW_MOUSE_BUTTON_LEFT:左ボタン 
	GLFW_MOUSE_BUTTON_RIGHT:右ボタン 
	return: 
	true：押されている 
	false:押されていない */ 
	static bool GetMouseButton(int button);
}; 

#endif