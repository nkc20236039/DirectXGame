#include "GameLoop.h"

bool GameLoop::initialize() {
	// �V�[���V�X�e����������
	SceneSystem::GetInstance().Init();
}

void update() {
	// �V�[���̍X�V
	SceneSystem::GetInstance().GetCurrentScene().tick();
}