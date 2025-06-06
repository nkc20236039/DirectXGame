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
	HWND hWnd;	// �E�B���h�E�n���h��
	HINSTANCE hInstance;	// �C���X�^���X�n���h��

private:
	// �E�B���h�E������������
	bool InitWindow();
	// �E�B���h�E�̃��b�Z�[�W����
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};