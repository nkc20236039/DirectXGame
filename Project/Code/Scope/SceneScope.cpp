#include "SceneScope.h"
#include "../Scene/MockScene.h"

void SceneScope::definer(SceneList& sceneList) {
	// ここでゲームのシーンを登録する
	sceneList.registerBootScene<MockScene>(std::make_shared<MockScene>());
}