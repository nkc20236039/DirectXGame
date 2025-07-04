#include "SceneSystem/SceneScope.h"

#include <memory>

#include "../../Code/Scene/MockScene.h"

using namespace UtX;

void SceneScope::definer(SceneList& sceneList) {
	// ここでゲームのシーンを登録する
	sceneList.registerBootScene<MockScene>(std::make_shared<MockScene>());
}