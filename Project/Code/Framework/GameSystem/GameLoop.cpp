#include <memory>
#include "GameLoop.h"
#include "./GameObject/GameObject.h"
#include "../Graphics/Shader.h"
#include "../Graphics/SpriteMesh.h"
#include "../Graphics/SpriteRenderer.h"

bool GameLoop::initialize(const DirectXApplication& graphicApp) {
	bool isCompleted = true;
	// �Q�[���I�u�W�F�N�g�����N���X�̏�����
	isCompleted = GameObject::init(graphicApp);
	// �G���[�`�F�b�N
	if (!isCompleted) { return false; }

	// �V�[���V�X�e����������
	SceneSystem::GetInstance().Init();
}

void update() {
	// �V�[���̍X�V
	SceneSystem::GetInstance().GetCurrentScene().tick();
}