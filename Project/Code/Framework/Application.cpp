#include "Application.h"

// �R���X�g���N�^/�f�X�g���N�^��`
Application::Application() : hWnd(nullptr), hInstance(nullptr) {}
Application::~Application() {}

bool Application::init() {
	if (!initWindow()) { return false; }

	// �E�B���h�E��\��
	ShowWindow(hWnd, SW_SHOWNORMAL);

	// �E�B���h�E���X�V
	UpdateWindow(hWnd);

	// �E�B���h�E�Ƀt�H�[�J�X
	SetFocus(hWnd);

	return true;
}

void Application::end() {

}

bool Application::initWindow() {
	// �E�B���h�E�N���X�o�^
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;	// �E�B���h�E�X�^�C��
	wcex.lpfnWndProc = wndProc;				// �E�B���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��ւ̃|�C���^
	wcex.cbClsExtra = 0;					// �E�B���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�̃o�C�g��
	wcex.cbWndExtra = 0;					// �E�B���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�̃o�C�g��
	wcex.hInstance = hInstance;				// ���̃N���X�̂��߂̃E�B���h�E�v���V�[�W��������n���h��
	wcex.hIcon = nullptr;					// �A�C�R��
	wcex.hCursor = nullptr;					// �}�E�X�J�[�\��
	wcex.hbrBackground = (HBRUSH)COLOR_WINDOW;// �E�B���h�E�w�i�F
	wcex.lpszMenuName = nullptr;			// �f�t�H���g���j���[��
	wcex.lpszClassName = CLASS_NAME;		// �E�B���h�E�N���X��
	wcex.hIconSm = nullptr;					// �������A�C�R��
	RegisterClassEx(&wcex);					// �E�B���h�E�N���X�o�^

	// �E�B���h�E���� �������̓E�B���h�E�n���h���A���s����null���Ԃ�
	hWnd = CreateWindow(
		CLASS_NAME,					// RegisterClass()�œo�^�����N���X�̖��O
		WINDOW_TITLE,				// �^�C�g���o�[
		WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,				// �E�B���h�E����x���W
		CW_USEDEFAULT,				// �E�B���h�E����y���W
		WINDOW_WIDTH,					// �E�B���h�E��
		WINDOW_HEIGHT,					// �E�B���h�E����
		nullptr,					// �e�E�B���h�E�̃n���h��
		nullptr,					// ���j���[�̃n���h��
		wcex.hInstance,				// �E�B���h�E���쐬���郂�W���[���̃n���h��
		nullptr						// WM_CREATE��LPARAM�ɓn�������l
	);

	// ����I��
	return true;
}

LRESULT CALLBACK Application::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CLOSE:		// ����{�^���������ꂽ���b�Z�[�W
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case WM_DESTROY:	// �E�B���h�E���I�����郁�b�Z�[�W
			PostQuitMessage(0);
			break;
		default:
			break;
	}

	// ����̃E�B���h�E�v���V�[�W�����Ăяo���ď�����Ԃ�
	return DefWindowProc(hWnd, message, wParam, lParam);
}