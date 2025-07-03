#include <Windows.h>

#include <cstdint>
#include <memory>
#include <string>

#include "System/DirectXApplication.h"
#include "System/GameLoop.h"

#pragma comment(lib,"winmm.lib")

using namespace UtX;

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

	GameLoop gameLoop = GameLoop();

	// ������
	if (!graphicApp->init()) { return 1; }

	// �Q�[���̏�����
	bool isComplete = gameLoop.init(*graphicApp);

	// ���������ɃG���[�����������ꍇ�̓Q�[�����I������
	if (!isComplete) { return 0; }

	MSG hMsg = {};	// ���b�Z�[�W�n���h����������
	// ���C�����[�v
	while (hMsg.message != WM_QUIT) {
		// ���b�Z�[�W�擾�����݂�
		if (PeekMessage(&hMsg, nullptr, 0, 0, PM_REMOVE)) {
			// �L�[�{�[�h���b�Z�[�W���當�����b�Z�[�W�𐶐�
			TranslateMessage(&hMsg);
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W��n��
			DispatchMessage(&hMsg);
		}
		// FPS����
		QueryPerformanceFrequency(&timeFrequency);
		QueryPerformanceCounter(&timeStart);
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