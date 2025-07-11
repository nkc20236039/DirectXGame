#pragma once

#include <string>
#include <list>
#include <memory>

#include "GameObject/Objects/Actor.h"
#include "GameObject/Objects/Camera2D.h"
#include "Graphics/SpriteMesh.h"
#include "Graphics/SpriteRenderer.h"
#include "Math/MathX.h"

namespace UtX {
	// �Q�[���I�u�W�F�N�g�̍쐬�Ӗ�
	class GameObject {
	public:
		// �V���O���g��
		static GameObject& getInstance();

		// �J�����쐬
		std::shared_ptr<Camera2D> create2DCamera(Transform transform, float zoom = 1.0f);

		// �A�N�^�[�쐬
		std::shared_ptr<Actor> createActor(std::string spritePath, Transform transform, uint32_t layer);

		// UI�쐬
		// std::shared_ptr<UI> createUI();

		// �X�V
		void update();

		// �����_�����O
		void render();

	private:
		DirectXApplication& application;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<SpriteMesh> spriteMesh;
		std::unique_ptr<SpriteRenderer> spriteRenderer;

		// �J����
		std::shared_ptr<Camera2D> mainCamera;
		// �����_�����O�������K�v�ȃA�N�^�[��ێ�
		std::list<std::shared_ptr<Actor>> actors;

		/* �������ƃV���O���g���̏��������鏈���ɕK�v�Ȃ���: */
		// ���������s����̂��Q�[�����\�z����GameLoop�N���X�݂̂Ɍ��肷��
		friend class GameLoop;

		// �R���X�g���N�^�̌Ăяo�����֎~
		GameObject(DirectXApplication& app);
		~GameObject() = default;

		// GameLoop���菉��������
		static bool init(DirectXApplication& app);

		// �C���X�^���X�쐬�`�F�b�N
		bool isInitialized = false;

		// �V���O���g��
		static GameObject* instance;
		// �R�s�[�A���[�u���֎~����
		GameObject(const GameObject&) = delete;
		GameObject(GameObject&&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject& operator=(GameObject&&) = delete;
	};
}