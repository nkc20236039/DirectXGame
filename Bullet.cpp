#include "../../Code/Actors/Bullet.h"

using namespace UtX;

constexpr float TOP_POSITION = 720.0f; // 画面最上部のY座標

void Bullet::Update(float deltaTime) {
	// 上へ移動し続ける
	Transform transform = bullet->getTransform();
	Vector2 position = transform.getPosition();
	position.y = position.y + speed;
	transform.setPosition(position);
	bullet->setTransform(transform);

	// スプライト分割
	Vector2 uvSplit = Vector2(1.0f / 4.0f, 1.0f);

	time += deltaTime;

	if (animationTime <= time) {
		uv.x = (float)(((int)uv.x + 1) % 4);

		time = 0.0f;
	}
	// 弾のアニメーション
	float uvX = uvSplit.x * uv.x;
	float uvY = uvSplit.y * uv.y;

	// 弾の頂点情報
	std::array<Vertex, 4> bulletVertexList = vertexList;

	bulletVertexList[0].uv = { uvX, 1 };
	bulletVertexList[1].uv = { uvX, 0 };
	bulletVertexList[2].uv = { uvX + uvSplit.x, 1 };
	bulletVertexList[3].uv = { uvX + uvSplit.x, 0 };

	bullet->setVertexList(bulletVertexList);

	if (TOP_POSITION < position.y) {
		// 画面外に出たら削除
		hasInstance = false;
		bullet.reset();
	}
}