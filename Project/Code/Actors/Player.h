#pragma once

#include <memory>

#include "GameObject/Objects/Actor.h"

class Player {
public:
	Player(std::shared_ptr<UtX::Actor> player, std::array<UtX::Vertex, 4> vertexList)
		:player(player), time(0.0f), speed(10.0f), animationTime(0.1f), uv(UtX::Vector2::zero), vertexList(vertexList) {
	}
	~Player() = default;
	void Update(float deltaTime);

private:
	float time;
	float speed;
	float animationTime;
	UtX::Vector2 uv;
	std::shared_ptr<UtX::Actor> player;
	std::array<UtX::Vertex, 4> vertexList;
};