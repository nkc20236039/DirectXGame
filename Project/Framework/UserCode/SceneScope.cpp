#include "SceneSystem/SceneScope.h"

#include <memory>

#include "../../Code/Scene/MockScene.h"

using namespace UtX;

void SceneScope::definer(SceneList& sceneList) {
	// �����ŃQ�[���̃V�[����o�^����
	sceneList.registerBootScene<MockScene>(std::make_shared<MockScene>());
}