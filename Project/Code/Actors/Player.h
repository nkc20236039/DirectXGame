#pragma once

#include <memory>

#include "GameObject/Objects/Actor.h"

class Player {
public:
	Player(std::shared_ptr<UtX::Actor> player, std::array<UtX::Vertex, 4> vertexList)
		:player(player), time(0.0f), speed(10.0f), animationTime(0.1f), uv(UtX::Vector2::zero), vertexList(vertexList) {
	}
	~Player() = default;
	// プレイヤーの更新
	void Update(float deltaTime);	
	// プレイヤーの位置を取得
	UtX::Vector2 GetPosition() { return player->getTransform().getPosition(); }

private:
	float time;		// 経過時間
	float speed;	// 移動速度
	float animationTime;	// アニメーションの再生間隔
	UtX::Vector2 uv;		// アニメーションUV
	std::shared_ptr<UtX::Actor> player;		// プレイヤーの実体
	std::array<UtX::Vertex, 4> vertexList;	// 頂点リスト
};