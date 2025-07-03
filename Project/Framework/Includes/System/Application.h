#pragma once

#include <Windows.h>

#include "../UserCode/ApplicationConfig.h"

namespace UtX {
	class Application {
	public:
		Application();
		~Application();

		virtual bool init();
		virtual void end();

	protected:
		HWND hWnd;	// �E�B���h�E�n���h��
		HINSTANCE hInstance;	// �C���X�^���X�n���h��

	private:
		// �E�B���h�E������������
		bool initWindow();
		// �E�B���h�E�̃��b�Z�[�W����
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}