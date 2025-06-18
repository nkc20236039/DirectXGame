#pragma once
#include <string>
#include <list>
#include <memory>
#include "Objects/Actor.h"
#include "../../Math/MathX.h"
#include "../../Graphics/SpriteMesh.h"
#include "../../Graphics/SpriteRenderer.h"

// �Q�[���I�u�W�F�N�g�̍쐬�Ӗ�
class GameObject {
public:
	// �V���O���g��
	static GameObject& GetInstance();

	// �J�����쐬
	void Create2DCamera();

	// �A�N�^�[�쐬
	std::shared_ptr<Actor> CreateActor(std::string spritePath, Vector2 position, Vector2 scale, Quaternion rotation, uint32_t layer);

	// �����_�����O
	void Render();
private:
	// �R���X�g���N�^
	GameObject() = default;
	~GameObject() = default;

	// �R�s�[�A���[�u���֎~����
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	// �����_�����O�������K�v�ȃA�N�^�[��ێ�
	std::list<std::shared_ptr<Actor>> actors;
};