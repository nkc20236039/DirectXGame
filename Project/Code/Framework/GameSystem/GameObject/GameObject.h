#pragma once
#include <string>
#include <list>
#include <memory>
#include "Objects/Actor.h"
#include "../../Math/MathX.h"
#include "../../Graphics/SpriteMesh.h"
#include "../../Graphics/SpriteRenderer.h"

// ゲームオブジェクトの作成責務
class GameObject {
public:
	// シングルトン
	static GameObject& getInstance();

	// カメラ作成
	void create2DCamera();

	// アクター作成
	std::shared_ptr<Actor> createActor(std::string spritePath, Transform transform, uint32_t layer);

	// レンダリング
	void render();
private:
	const DirectXApplication& application;
	std::unique_ptr<Shader> shader;
	std::unique_ptr<SpriteMesh> spriteMesh;
	std::unique_ptr<SpriteRenderer> spriteRenderer;

	/* 初期化とシングルトンの準備をする処理に必要なもの: */
		// 初期化を行えるのをゲームを構築するGameLoopクラスのみに限定する
	friend class GameLoop;

	// コンストラクタの呼び出しを禁止
	GameObject(const DirectXApplication& app);
	~GameObject() = default;

	// GameLoop限定初期化処理
	static bool init(const DirectXApplication& app);

	// インスタンス作成チェック
	bool isInitialized = false;

	// シングルトン
	static GameObject* instance;
	// コピー、ムーブを禁止する
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	// レンダリング処理が必要なアクターを保持
	std::list<std::shared_ptr<Actor>> actors;
};