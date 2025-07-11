#include "../../Code/Scene/MockScene.h"

#include <array>

#include "GameObject/GameObject.h"

using namespace UtX;

void MockScene::init() {
	// 初期頂点情報
	vertexList[0].position = { -0.5f, -0.5f, 0.0f };
	vertexList[1].position = { -0.5f, 0.5f, 0.0f };
	vertexList[2].position = { 0.5f, -0.5f, 0.0f };
	vertexList[3].position = { 0.5f, 0.5f, 0.0f };

	vertexList[0].uv = { 0.0f, 1.0f };
	vertexList[1].uv = { 0.0f, 0.0f };
	vertexList[2].uv = { 1.0f, 1.0f };
	vertexList[3].uv = { 1.0f, 0.0f };

	for (int32_t i = 0; i < 4; i++) {
		// 頂点の色
		vertexList[i].color = { 1.0f, 0.0f, 1.0f, 1.0f };
		// ノーマルマップ
		vertexList[i].normal = { 0.0f, 0.0f, 1.0f };
	}
}

void MockScene::enter() {
	GameObject::getInstance().create2DCamera(Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0.2f)
		->setBackgroundColor(Color(0.2f, 0.2f, 0.2f));
	backGround = GameObject::getInstance().createActor(".\\Assets\\Sprite\\GBackTex.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0);
	auto playerObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\MyChar.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0);

	player = std::make_shared<Player>(playerObject, vertexList);
}

void MockScene::update() {
	float deltaTime = 1.0f / 60.0f;
	player->Update(deltaTime);

	backGround->setVertexList(vertexList);
}

void MockScene::exit() {
}
