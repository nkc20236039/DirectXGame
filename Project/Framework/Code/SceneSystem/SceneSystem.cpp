#include "SceneSystem/SceneSystem.h"

#include "SceneSystem/SceneScope.h"

using namespace UtX;

SceneSystem* SceneSystem::instance = nullptr;

SceneSystem::SceneSystem() {
	// �V�[���̃��X�g���쐬
	sceneList = std::make_unique<SceneList>();
}

SceneSystem& SceneSystem::getInstance() {
	// �擾�������C���X�^���X�����݂��Ȃ��ꍇ
	if (instance == nullptr) {
		instance = new SceneSystem();
	}
	return *instance;
}

bool SceneSystem::init() {
	// �V�[���̓o�^
	SceneScope sceneScope = SceneScope();

	sceneScope.definer(*sceneList);

	// �N���V�[�����o�^����Ă��Ȃ��ꍇ�I������
	if (!sceneList->isBootSceneRegistered()) { return false; }

	// �S�ẴV�[����������
	auto allScene = sceneList->getAllScenes();
	for (auto scene : allScene) {
		scene->init();
	}

	// �N���V�[�������[�v�ɓo�^
	currentScene = sceneList->getScene(sceneList->getBootSceneIndex());

	return true;
}

IScene& SceneSystem::getCurrentScene() {
	return *currentScene;
}