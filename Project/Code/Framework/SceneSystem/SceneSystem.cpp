#include "SceneSystem.h"
#include "../../Scope/SceneScope.h"

SceneSystem::SceneSystem() {
	// シーンのリストを作成
	sceneList = std::make_unique<SceneList>();
}

SceneSystem& SceneSystem::GetInstance() {
	// 取得したいインスタンスが存在しない場合
	if (instance == nullptr) {
		instance = new SceneSystem();
	}
	return *instance;
}

bool SceneSystem::Init() {
	// シーンの登録
	SceneScope sceneScope = SceneScope();

	sceneScope.definer(*sceneList);

	// 起動シーンが登録されていない場合終了する
	if (!sceneList->isBootSceneRegistered()) { return false; }

	// 起動シーンをループに登録
	currentScene = sceneList->getScene(sceneList->getBootSceneIndex());
}

IScene& SceneSystem::GetCurrentScene() {
	return *currentScene;
}