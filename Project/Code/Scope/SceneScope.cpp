#include "SceneScope.h"
#include "../Scene/MockScene.h"

void SceneScope::definer(SceneList& sceneList) {
	// �����ŃQ�[���̃V�[����o�^����
	sceneList.registerBootScene<MockScene>(std::make_shared<MockScene>());
}