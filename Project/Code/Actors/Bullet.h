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
	bool hasInstance;	// 弾の実態を所持しているか
	float time;			// 経過時間
	float speed;		// 移動速度
	float animationTime;	// アニメーションの再生間隔
	UtX::Vector2 uv;		// アニメーションUV
	std::shared_ptr<UtX::Actor> bullet;		// 弾の実体
	std::array<UtX::Vertex, 4> vertexList;	// 頂点リスト
};