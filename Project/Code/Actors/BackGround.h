#pragma once

#include <memory>

#include "GameObject/Objects/Actor.h"

class BackGround {
public:
	BackGround(std::shared_ptr<UtX::Actor> backGround, std::array<UtX::Vertex, 4> vertexList)
		:backGround(backGround), animationTime(-0.1f), uv(UtX::Vector2::zero), vertexList(vertexList) {
	}
	~BackGround() = default;
	void Update(float deltaTime);

private:
	float animationTime;	// �X�N���[������
	UtX::Vector2 uv;		// �ړ����x
	std::shared_ptr<UtX::Actor> backGround;	// �w�i�̎���
	std::array<UtX::Vertex, 4> vertexList;	// ���_���X�g
};