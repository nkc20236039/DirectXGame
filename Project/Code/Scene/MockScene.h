#pragma once

#include <memory>
#include <vector>

#include "SceneSystem/IScene.h"
#include "GameObject/Objects/Actor.h"
#include "../../Code/Actors/Player.h"
#include "../../Code/Actors/BackGround.h"
#include "../../Code/Actors/Bullet.h"

class MockScene : public UtX::IScene {
public:
	MockScene() :time(0.0f), shotSpan(0.1f), vertexList{} {}
	~MockScene() = default;

	// Sceneに必要な関数
	void init() override;
	void enter() override;
	void update() override;
	void exit() override;
private:
	float time;	// 経過時間
	float shotSpan;	// 弾を撃つ間隔
	std::unique_ptr<Player> player;	// プレイヤーの管理クラス
	std::unique_ptr<BackGround> backGround;	// 背景の管理クラス
	std::vector<std::unique_ptr<Bullet>> bullets;	// 弾の管理クラス
	std::array<UtX::Vertex, 4> vertexList;	// 初期頂点情報
};