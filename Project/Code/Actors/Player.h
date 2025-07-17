#pragma once

#include <memory>

#include "GameObject/Objects/Actor.h"

class Player {
public:
	Player(std::shared_ptr<UtX::Actor> player, std::array<UtX::Vertex, 4> vertexList)
		:player(player), time(0.0f), speed(10.0f), animationTime(0.1f), uv(UtX::Vector2::zero), vertexList(vertexList) {
	}
	~Player() = default;
	// �v���C���[�̍X�V
	void Update(float deltaTime);	
	// �v���C���[�̈ʒu���擾
	UtX::Vector2 GetPosition() { return player->getTransform().getPosition(); }

private:
	float time;		// �o�ߎ���
	float speed;	// �ړ����x
	float animationTime;	// �A�j���[�V�����̍Đ��Ԋu
	UtX::Vector2 uv;		// �A�j���[�V����UV
	std::shared_ptr<UtX::Actor> player;		// �v���C���[�̎���
	std::array<UtX::Vertex, 4> vertexList;	// ���_���X�g
};