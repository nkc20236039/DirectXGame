#include <Windows.h>
#include <cstdint>
#include <memory>
#include <string>
#include "./Framework/Graphics/DirectXApplication.h"
#include "./Framework/GameSystem/GameLoop.h"
#include "./Framework/Graphics/Shader.h"
#include "./Framework/Graphics/SpriteMesh.h"

#pragma comment(lib,"winmm.lib")

// FPS����
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
	std::unique_ptr<Shader> shader = std::make_unique<Shader>(*graphicApp);
	std::unique_ptr<SpriteMesh> spriteMesh = std::make_unique<SpriteMesh>(*graphicApp);
	std::unique_ptr<SpriteRenderer> spriteRenderer = std::make_unique<SpriteRenderer>(*graphicApp);
	GameLoop gameLoop = GameLoop();

	// ������
	if (!graphicApp->init()) { return 1; }
	// StandardShaderResource���擾
	std::shared_ptr<ShaderResource> shaderResource = std::make_shared<ShaderResource>();
	bool isComplete = shader->CreateStandardShader(
		".\\Assets\\Shader\\Standard\\VertexShader.hlsl",
		".\\Assets\\Shader\\Standard\\PixelShader.hlsl",
		shaderResource);
	if (!isComplete) { return 1; }

	spriteMesh->init(shaderResource);
	// �Q�[���̏�����
	bool isComplete = gameLoop.initialize();

	// ���������ɃG���[�����������ꍇ�̓Q�[�����I������
	if (!isComplete) { return 0; }

	MSG hMsg = {};	// ���b�Z�[�W�n���h����������
	float color = 0.0f;
	float time = 0.0f;
	// ���C�����[�v
	while (hMsg.message != WM_QUIT) {
		// ���b�Z�[�W�擾�����݂�
		if (PeekMessage(&hMsg, nullptr, 0, 0, PM_REMOVE)) {
			// �L�[�{�[�h���b�Z�[�W���當�����b�Z�[�W�𐶐�
			TranslateMessage(&hMsg);
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W��n��
			DispatchMessage(&hMsg);
		}
		time += 0.05f;
		color = std::cos(time);
		// FPS����
		QueryPerformanceFrequency(&timeFrequency);
		QueryPerformanceCounter(&timeStart);
		graphicApp->renderBegin(color, color, color, 1.0f);
		spriteMesh->rendering(spriteRenderer->getOrCreateSprite(".\\Assets\\Sprite\\ColorfulSprite.png"));
		graphicApp->renderEnd();
		// �Q�[�����[�v�̍X�V
		gameLoop.update();
		FrameRate();
	}

	return 0;
}

void FrameRate() {
	// ���݂̎��Ԃ��擾
	QueryPerformanceCounter(&timeEnd);
	// �o�ߎ��Ԃ����߂�
	frameTime
		= static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart)
		/ static_cast<float>(timeFrequency.QuadPart);

	// �������Ԃ��\���葁���ꍇ
	if (frameTime < MIN_FRAME_TIME) {
		// �~���b�ɕϊ�����
		DWORD sleepTime = static_cast<DWORD>((MIN_FRAME_TIME - frameTime) * 1000);

		timeBeginPeriod(1);	// ����\���グ��
		Sleep(sleepTime);	// �ҋ@
		timeEndPeriod(1);	// ����\��߂�

		return;
	}
	// �������Ԃ����������ꍇ�͏I�����ԂƊJ�n���Ԃ����ւ���
	timeStart = timeEnd;
}