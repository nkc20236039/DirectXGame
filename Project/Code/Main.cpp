#include <Windows.h>
#include <cstdint>
#include <memory>
#include <string>
#include "./Framework/Graphics/Direct3D.h"
#include "./Framework/GameSystem/PlayerLoop.h"
#include "./Framework/Graphics/Shader.h"
#include "./Framework/Graphics/SpriteMesh.h"

#pragma comment(lib,"winmm.lib")

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
	std::unique_ptr<Direct3D> graphicApp = std::make_unique<Direct3D>();
	std::unique_ptr<Shader> shader = std::make_unique<Shader>(*graphicApp);
	std::unique_ptr<SpriteMesh> spriteMesh = std::make_unique<SpriteMesh>(*graphicApp);
	std::unique_ptr<SpriteRenderer> spriteRenderer = std::make_unique<SpriteRenderer>(*graphicApp);
	// std::unique_ptr<PlayerLoop> playerLoop = std::make_unique<PlayerLoop>();

	// 初期化
	if (!graphicApp->init()) { return 1; }
	// StandardShaderResourceを取得
	std::shared_ptr<ShaderResource> shaderResource = std::make_shared<ShaderResource>();
	bool isComplete = shader->CreateStandardShader(
		".\\Assets\\Shader\\Standard\\VertexShader.hlsl",
		".\\Assets\\Shader\\Standard\\PixelShader.hlsl",
		shaderResource);
	if (!isComplete) { return 1; }

	spriteMesh->init(shaderResource);

	MSG hMsg = {};	// メッセージハンドルを初期化
	float color = 0.0f;
	float time = 0.0f;
	// メインループ
	while (hMsg.message != WM_QUIT) {
		// メッセージ取得を試みる
		if (PeekMessage(&hMsg, nullptr, 0, 0, PM_REMOVE)) {
			// キーボードメッセージから文字メッセージを生成
			TranslateMessage(&hMsg);
			// ウィンドウプロシージャにメッセージを渡す
			DispatchMessage(&hMsg);
		}
		time += 0.05f;
		color = std::cos(time);
		QueryPerformanceFrequency(&timeFrequency);	// FPS制御
		QueryPerformanceCounter(&timeStart);		// FPS制御
		graphicApp->renderBegin(color, color, color, 1.0f);
		spriteMesh->rendering(spriteRenderer->getOrCreateSprite(".\\Assets\\Sprite\\ColorfulSprite.png"));
		graphicApp->renderEnd();
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