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
	static GameObject& GetInstance();

	// カメラ作成
	void Create2DCamera();

	// アクター作成
	std::shared_ptr<Actor> CreateActor(std::string spritePath, Vector2 position, Vector2 scale, Quaternion rotation, uint32_t layer);

	// レンダリング
	void Render();
private:
	// コンストラクタ
	GameObject() = default;
	~GameObject() = default;

	// コピー、ムーブを禁止する
	GameObject(const GameObject&) = delete;
	GameObject(GameObject&&) = delete;
	GameObject& operator=(const GameObject&) = delete;
	GameObject& operator=(GameObject&&) = delete;

	// レンダリング処理が必要なアクターを保持
	std::list<std::shared_ptr<Actor>> actors;
};