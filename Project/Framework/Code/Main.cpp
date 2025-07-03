#include <Windows.h>

#include <cstdint>
#include <memory>
#include <string>

#include "System/DirectXApplication.h"
#include "System/GameLoop.h"

#pragma comment(lib,"winmm.lib")

using namespace UtX;

// FPS制御
float frameTime = 0;
LARGE_INTEGER timeStart = { 0 };
LARGE_INTEGER timeEnd = { 0 };
LARGE_INTEGER timeFrequency = { 0 };

void FrameRate();

int32_t APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int32_t nCmdShow) {
	std::unique_ptr<DirectXApplication> graphicApp = std::make_unique<DirectXApplication>();

	GameLoop gameLoop = GameLoop();

	// 初期化
	if (!graphicApp->init()) { return 1; }

	// ゲームの初期化
	bool isComplete = gameLoop.init(*graphicApp);

	// 初期化中にエラーが発生した場合はゲームを終了する
	if (!isComplete) { return 0; }

	MSG hMsg = {};	// メッセージハンドルを初期化
	// メインループ
	while (hMsg.message != WM_QUIT) {
		// メッセージ取得を試みる
		if (PeekMessage(&hMsg, nullptr, 0, 0, PM_REMOVE)) {
			// キーボードメッセージから文字メッセージを生成
			TranslateMessage(&hMsg);
			// ウィンドウプロシージャにメッセージを渡す
			DispatchMessage(&hMsg);
		}
		// FPS制御
		QueryPerformanceFrequency(&timeFrequency);
		QueryPerformanceCounter(&timeStart);
		// ゲームループの更新
		gameLoop.update();
		FrameRate();
	}

	return 0;
}

void FrameRate() {
	// 現在の時間を取得
	QueryPerformanceCounter(&timeEnd);
	// 経過時間を求める
	frameTime
		= static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart)
		/ static_cast<float>(timeFrequency.QuadPart);

	// 処理時間が予定より早い場合
	if (frameTime < MIN_FRAME_TIME) {
		// ミリ秒に変換する
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1);	// 分解能を上げる
		Sleep(sleepTime);	// 待機
		timeEndPeriod(1);	// 分解能を戻す

		return;
	}
	// 処理時間が長かった場合は終了時間と開始時間を入れ替える
	timeStart = timeEnd;
}