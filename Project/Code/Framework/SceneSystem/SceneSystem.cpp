#include "SceneSystem.h"
#include "../../Scope/SceneScope.h"

SceneSystem::SceneSystem() {
	// �V�[���̃��X�g���쐬
	sceneList = std::make_unique<SceneList>();
}

bool SceneSystem::Init() {
	// �V�[���̓o�^
	SceneScope sceneScope = SceneScope();

	sceneScope.definer(*sceneList);
}