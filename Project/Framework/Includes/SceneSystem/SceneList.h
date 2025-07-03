#pragma once

#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>

#include "SceneSystem/IScene.h"

namespace UtX {
	// ISceneを継承しているかの条件
	template <typename T>
	concept DerivedIScene = std::is_base_of<IScene, T>::value;

	class SceneList {
	public:
		SceneList()
			: existBootScene(false), bootSceneIndex(typeid(void)) {
		}
		~SceneList() = default;

		/// <summary>
		/// シーンをゲームサイクルに登録します
		/// </summary>
		/// <typeparam name="T">ISceneを継承したクラス</typeparam>
		/// <param name="scene">シーンクラスのインスタンス</param>
		template<DerivedIScene T>
		void registerScene(std::shared_ptr<T> scene) {
			sceneContainer[typeid(T)] = scene;
		}

		/// <summary>
		/// ゲーム開始時最初に実行されるシーンを指定します
		/// </summary>
		/// <typeparam name="T">ISceneを継承したクラス</typeparam>
		/// <param name="scene">シーンクラスのインスタンス</param>
		template<DerivedIScene T>
		void registerBootScene(std::shared_ptr<T> scene) {
			registerScene<T>(scene);
			bootSceneIndex = typeid(T);
			existBootScene = true;
		}

		// TODO:: ここから下はインターフェースでカプセル化する
		template<DerivedIScene T>
		T getScene() {
			return getScene(typeid(T));
		}

		std::shared_ptr<IScene> getScene(std::type_index type);

		std::vector<std::shared_ptr<IScene>> getAllScenes();
		bool isBootSceneRegistered();
		std::type_index getBootSceneIndex();

	private:
		bool existBootScene;
		std::type_index bootSceneIndex;
		std::unordered_map<std::type_index, std::shared_ptr<IScene>> sceneContainer = {};
	};
}