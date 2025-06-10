#include "SceneSystem.h"
#include "../../Scope/SceneScope.h"

SceneSystem::SceneSystem() {
	// シーンのリストを作成
	sceneList = std::make_unique<SceneList>();
}

bool SceneSystem::Init() {
	// シーンの登録
	SceneScope sceneScope = SceneScope();

	sceneScope.definer(*sceneList);
}