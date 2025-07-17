#pragma once

#include <memory>

#include "GameObject/Objects/Actor.h"

class Bullet {
public:
	Bullet(std::shared_ptr<UtX::Actor> bullet, std::array<UtX::Vertex, 4> vertexList)
		:hasInstance(true), bullet(bullet), time(0.0f), speed(20.0f), animationTime(0.1f), uv(UtX::Vector2::zero), vertexList(vertexList) {
	}
	~Bullet() = default;
	void Update(float deltaTime);
	bool HasInstance() { return hasInstance; }

private:
	bool hasInstance;	// �e�̎��Ԃ��������Ă��邩
	float time;			// �o�ߎ���
	float speed;		// �ړ����x
	float animationTime;	// �A�j���[�V�����̍Đ��Ԋu
	UtX::Vector2 uv;		// �A�j���[�V����UV
	std::shared_ptr<UtX::Actor> bullet;		// �e�̎���
	std::array<UtX::Vertex, 4> vertexList;	// ���_���X�g
};