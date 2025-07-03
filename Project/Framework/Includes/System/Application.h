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
		HWND hWnd;	// ウィンドウハンドル
		HINSTANCE hInstance;	// インスタンスハンドル

	private:
		// ウィンドウを初期化する
		bool initWindow();
		// ウィンドウのメッセージ処理
		static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}