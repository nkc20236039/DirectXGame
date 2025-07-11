#pragma once

#include <string>
#include <list>
#include <memory>

#include "GameObject/Objects/Actor.h"
#include "GameObject/Objects/Camera2D.h"
#include "Graphics/SpriteMesh.h"
#include "Graphics/SpriteRenderer.h"
#include "Math/MathX.h"

namespace UtX {
	// ゲームオブジェクトの作成責務
	class GameObject {
	public:
		// シングルトン
		static GameObject& getInstance();

		// カメラ作成
		std::shared_ptr<Camera2D> create2DCamera(Transform transform, float zoom = 1.0f);

		// アクター作成
		std::shared_ptr<Actor> createActor(std::string spritePath, Transform transform, uint32_t layer);

		// UI作成
		// std::shared_ptr<UI> createUI();

		// 更新
		void update();

		// レンダリング
		void render();

	private:
		DirectXApplication& application;
		std::unique_ptr<Shader> shader;
		std::unique_ptr<SpriteMesh> spriteMesh;
		std::unique_ptr<SpriteRenderer> spriteRenderer;

		// カメラ
		std::shared_ptr<Camera2D> mainCamera;
		// レンダリング処理が必要なアクターを保持
		std::list<std::shared_ptr<Actor>> actors;

		/* 初期化とシングルトンの準備をする処理に必要なもの: */
		// 初期化を行えるのをゲームを構築するGameLoopクラスのみに限定する
		friend class GameLoop;

		// コンストラクタの呼び出しを禁止
		GameObject(DirectXApplication& app);
		~GameObject() = default;

		// GameLoop限定初期化処理
		static bool init(DirectXApplication& app);

		// インスタンス作成チェック
		bool isInitialized = false;

		// シングルトン
		static GameObject* instance;
		// コピー、ムーブを禁止する
		GameObject(const GameObject&) = delete;
		GameObject(GameObject&&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject& operator=(GameObject&&) = delete;
	};
}