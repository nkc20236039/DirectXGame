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
	float animationTime;	// スクロール時間
	UtX::Vector2 uv;		// 移動速度
	std::shared_ptr<UtX::Actor> backGround;	// 背景の実体
	std::array<UtX::Vertex, 4> vertexList;	// 頂点リスト
};