#include "GameLoop.h"

bool GameLoop::initialize() {
	// シーンシステムを初期化
	SceneSystem::GetInstance().Init();
}

void update() {
	// シーンの更新
	SceneSystem::GetInstance().GetCurrentScene().tick();
}