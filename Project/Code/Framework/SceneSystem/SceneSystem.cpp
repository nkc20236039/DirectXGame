#include "SceneSystem.h"
#include "../../Scope/SceneScope.h"

SceneSystem::SceneSystem() {
	// �V�[���̃��X�g���쐬
	sceneList = std::make_unique<SceneList>();
}

SceneSystem& SceneSystem::GetInstance() {
	// �擾�������C���X�^���X�����݂��Ȃ��ꍇ
	if (instance == nullptr) {
		instance = new SceneSystem();
	}
	return *instance;
}

bool SceneSystem::Init() {
	// �V�[���̓o�^
	SceneScope sceneScope = SceneScope();

	sceneScope.definer(*sceneList);

	// �N���V�[�����o�^����Ă��Ȃ��ꍇ�I������
	if (!sceneList->isBootSceneRegistered()) { return false; }

	// �N���V�[�������[�v�ɓo�^
	currentScene = sceneList->getScene(sceneList->getBootSceneIndex());
}

IScene& SceneSystem::GetCurrentScene() {
	return *currentScene;
}