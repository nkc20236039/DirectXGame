#include "SceneSystem/SceneSystem.h"

#include "SceneSystem/SceneScope.h"

using namespace UtX;

SceneSystem* SceneSystem::instance = nullptr;

SceneSystem::SceneSystem() {
	// シーンのリストを作成
	sceneList = std::make_unique<SceneList>();
}

SceneSystem& SceneSystem::getInstance() {
	// 取得したいインスタンスが存在しない場合
	if (instance == nullptr) {
		instance = new SceneSystem();
	}
	return *instance;
}

bool SceneSystem::init() {
	// シーンの登録
	SceneScope sceneScope = SceneScope();

	sceneScope.definer(*sceneList);

	// 起動シーンが登録されていない場合終了する
	if (!sceneList->isBootSceneRegistered()) { return false; }

	// 全てのシーンを初期化
	auto allScene = sceneList->getAllScenes();
	for (auto scene : allScene) {
		scene->init();
	}

	// 起動シーンをループに登録
	currentScene = sceneList->getScene(sceneList->getBootSceneIndex());

	return true;
}

IScene& SceneSystem::getCurrentScene() {
	return *currentScene;
}