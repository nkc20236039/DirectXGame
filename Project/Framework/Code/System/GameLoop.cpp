#include "System/GameLoop.h"

#include <memory>

#include "GameObject/GameObject.h"
#include "Graphics/Shader.h"
#include "Graphics/SpriteMesh.h"
#include "Graphics/SpriteRenderer.h"

using namespace UtX;

bool GameLoop::init(DirectXApplication& graphicApp) {
	bool isCompleted = true;
	// ゲームオブジェクト生成クラスの初期化
	isCompleted = GameObject::init(graphicApp);
	// エラーチェック
	if (!isCompleted) { return false; }

	// シーンシステムを初期化
	isCompleted = SceneSystem::getInstance().init();
	// エラーチェック
	if (!isCompleted) { return false; }

	// 初期シーンの入力処理を実行
	SceneSystem::getInstance().getCurrentScene().enter();

	return true;
}

void GameLoop::update() {
	// シーンの更新
	SceneSystem::getInstance().getCurrentScene().update();
	// 全オブジェクトの描画
	GameObject::getInstance().render();
}