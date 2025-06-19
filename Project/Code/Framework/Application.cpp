#include "Application.h"

// コンストラクタ/デストラクタ定義
Application::Application() : hWnd(nullptr), hInstance(nullptr) {}
Application::~Application() {}

bool Application::init() {
	if (!initWindow()) { return false; }

	// ウィンドウを表示
	ShowWindow(hWnd, SW_SHOWNORMAL);

	// ウィンドウを更新
	UpdateWindow(hWnd);

	// ウィンドウにフォーカス
	SetFocus(hWnd);

	return true;
}

void Application::end() {

}

bool Application::initWindow() {
	// ウィンドウクラス登録
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// ウィンドウスタイル
	wcex.lpfnWndProc = wndProc;				// ウィンドウのメッセージを処理するコールバック関数へのポインタ
	wcex.cbClsExtra = 0;					// ウィンドウクラス構造体の後ろに割り当てる補足のバイト数
	wcex.cbWndExtra = 0;					// ウィンドウインスタンスの後ろに割り当てる補足のバイト数
	wcex.hInstance = hInstance;				// このクラスのためのウィンドウプロシージャがあるハンドル
	wcex.hIcon = nullptr;					// アイコン
	wcex.hCursor = nullptr;					// マウスカーソル
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;// ウィンドウ背景色
	wcex.lpszMenuName = nullptr;			// デフォルトメニュー名
	wcex.lpszClassName = CLASS_NAME;		// ウィンドウクラス名
	wcex.hIconSm = nullptr;					// 小さいアイコン
	RegisterClassEx(&wcex);					// ウィンドウクラス登録

	// ウィンドウ生成 成功時はウィンドウハンドル、失敗時はnullが返る
	hWnd = CreateWindow(
		CLASS_NAME,					// RegisterClass()で登録したクラスの名前
		WINDOW_TITLE,				// タイトルバー
		WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,// ウィンドウスタイル
		CW_USEDEFAULT,				// ウィンドウ左上x座標
		CW_USEDEFAULT,				// ウィンドウ左上y座標
		WINDOW_WIDTH,					// ウィンドウ幅
		WINDOW_HEIGHT,					// ウィンドウ高さ
		nullptr,					// 親ウィンドウのハンドル
		nullptr,					// メニューのハンドル
		wcex.hInstance,				// ウィンドウを作成するモジュールのハンドル
		nullptr						// WM_CREATEでLPARAMに渡したい値
	);

	// 正常終了
	return true;
}

LRESULT CALLBACK Application::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CLOSE:		// 閉じるボタンが押されたメッセージ
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case WM_DESTROY:	// ウィンドウが終了するメッセージ
			PostQuitMessage(0);
			break;
		default:
			break;
	}

	// 既定のウィンドウプロシージャを呼び出して処理を返す
	return DefWindowProc(hWnd, message, wParam, lParam);
}