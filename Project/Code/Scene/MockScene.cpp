#include "../../Code/Scene/MockScene.h"

#include <array>

#include "GameObject/GameObject.h"

using namespace UtX;

void MockScene::init() {
	// 初期頂点情報
	vertexList[0].position = { -128.0f, -128.0f, 0.0f };
	vertexList[1].position = { -128.0f, 128.0f, 0.0f };
	vertexList[2].position = { 128.0f, -128.0f, 0.0f };
	vertexList[3].position = { 128.0f, 128.0f, 0.0f };

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
	// カメラの作成
	GameObject::getInstance().create2DCamera(Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0.5f)
		->setBackgroundColor(Color(0.2f, 0.2f, 0.2f));
	// 背景の作成(GBackTex.png)
	auto backGroundObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\GBackTex.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(10.0f, 10.0f)), 0);
	// プレイヤーの作成(MyChar.png)
	auto playerObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\MyChar.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(0.75f, 0.75f)), 2);
	// TODO:: アクターの更新処理にコンポーネントを追加する処理を作成してUpdateを同期する仕組みを作る
	// プレイヤーの管理クラス
	player = std::make_unique<Player>(playerObject, vertexList);
	// 背景の管理クラス
	backGround = std::make_unique<BackGround>(backGroundObject, vertexList);
}

void MockScene::update() {
	// 仮のフレーム時間を計算
	float deltaTime = 1.0f / 60.0f;	// コンパイル時に最適化
	// プレイヤーの更新
	player->Update(deltaTime);
	// 背景の更新
	backGround->Update(deltaTime);

	// 時間を加算
	time += deltaTime;

	// スペースキーが押されていて、弾の発射間隔が経過している場合
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && shotSpan < time) {
		// 弾のアクターを作成(MyShot.png)
		auto bulletObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\MyShot.png", Transform(player->GetPosition(), 0.0f, Vector2(0.5f, 0.5f)), 1);
		// 配列に弾を追加
		bullets.push_back(std::make_unique<Bullet>(bulletObject, vertexList));
		// 時間を初期化
		time = 0;
	}

	// 弾がない場合は何もしない
	if (bullets.empty()) { return; }

	// 各弾の更新
	for (auto bullet = bullets.begin(); bullet != bullets.end();) {
		// 弾の実態が削除されている場合
		if (!(*bullet)->HasInstance()) {
			bullet = bullets.erase(bullet);	// 弾の管理終了
			continue;
		}

		// 弾の更新
		(*bullet)->Update(deltaTime);
		bullet++;	// 次の弾へ
	}
}

void MockScene::exit() {
}
