#include <memory>
#include "GameLoop.h"
#include "./GameObject/GameObject.h"
#include "../Graphics/Shader.h"
#include "../Graphics/SpriteMesh.h"
#include "../Graphics/SpriteRenderer.h"

bool GameLoop::initialize(const DirectXApplication& graphicApp) {
	bool isCompleted = true;
	// ゲームオブジェクト生成クラスの初期化
	isCompleted = GameObject::init(graphicApp);
	// エラーチェック
	if (!isCompleted) { return false; }

	// シーンシステムを初期化
	SceneSystem::GetInstance().Init();
}

void update() {
	// シーンの更新
	SceneSystem::GetInstance().GetCurrentScene().tick();
}