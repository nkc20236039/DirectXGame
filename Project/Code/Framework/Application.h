#pragma once
#include <Windows.h>
#include "ApplicationConfig.h"

class Application {
public:
	Application();
	~Application();

	virtual bool Init();
	virtual void End();

protected:
	HWND hWnd;	// ウィンドウハンドル
	HINSTANCE hInstance;	// インスタンスハンドル

private:
	// ウィンドウを初期化する
	bool InitWindow();
	// ウィンドウのメッセージ処理
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};