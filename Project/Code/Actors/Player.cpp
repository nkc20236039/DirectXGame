#include "../../Code/Actors/Player.h"

using namespace UtX;

void Player::Update(float deltaTime) {
	Vector2 input = Vector2::zero;
	// 入力チェック
	if (GetAsyncKeyState(VK_UP) & 0x8000) {		// 上
		input.y = 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	// 下
		input.y = -1.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	// 右
		uv.y = 1;
		input.x = 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	// 左
		uv.y = 2;
		input.x = -1.0f;
	}
	// 入力がない場合アニメーションを待機状態にする
	if (input == Vector2::zero) {
		uv.y = 0;
	}
	else {	// 入力があるときは移動
		// ノーマライズ
		input = input.Normalize();

		// 移動
		Transform transform = player->getTransform();
		Vector2 position = transform.getPosition();
		position.x = position.x + input.x * speed;
		position.y = position.y + input.y * speed;
		transform.setPosition(position);
		player->setTransform(transform);
	}

	// スプライト分割
	Vector2 uvSplit = Vector2(1.0f / 4.0f, 1.0f / 4.0f);

	time += deltaTime;

	// プレイヤーの頂点情報
	std::array<Vertex, 4> playerVertexList = vertexList;

	if (animationTime <= time) {
		uv.x = (int)(uv.x + 1) % 4;

		time = 0.0f;
	}
	// プレイヤーのアニメーション
	float uvX = uvSplit.x * uv.x;
	float uvY = uvSplit.y * uv.y;

	playerVertexList[0].uv = { uvX, uvY + uvSplit.y };
	playerVertexList[1].uv = { uvX, uvY };
	playerVertexList[2].uv = { uvX + uvSplit.x, uvY + uvSplit.y };
	playerVertexList[3].uv = { uvX + uvSplit.x, uvY };

	player->setVertexList(playerVertexList);
}