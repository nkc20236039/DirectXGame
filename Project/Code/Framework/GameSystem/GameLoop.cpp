#include <memory>
#include "GameLoop.h"
#include "./GameObject/GameObject.h"
#include "../Graphics/Shader.h"
#include "../Graphics/SpriteMesh.h"
#include "../Graphics/SpriteRenderer.h"

bool GameLoop::init(DirectXApplication& graphicApp) {
	bool isCompleted = true;
	// �Q�[���I�u�W�F�N�g�����N���X�̏�����
	isCompleted = GameObject::init(graphicApp);
	// �G���[�`�F�b�N
	if (!isCompleted) { return false; }

	// �V�[���V�X�e����������
	isCompleted = SceneSystem::getInstance().init();
	// �G���[�`�F�b�N
	if (!isCompleted) { return false; }

	return true;
}

void GameLoop::update() {
	// �V�[���̍X�V
	SceneSystem::getInstance().getCurrentScene().update();
	// �S�I�u�W�F�N�g�̕`��
	GameObject::getInstance().render();
}