#pragma once
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>
#include "../../Scope/SceneScope.h"
#include "IScene.h"

// ISceneを継承しているかの条件
template <typename T>
concept DerivedIScene = std::is_base_of<IScene, T>::value;

class SceneList {
public:
	/// <summary>
	/// シーンをゲームサイクルに登録します
	/// </summary>
	/// <typeparam name="T">ISceneを継承したクラス</typeparam>
	/// <param name="scene">シーンクラスのインスタンス</param>
	template<DerivedIScene T>
	void Register(T scene);

	/// <summary>
	/// ゲーム開始時最初に実行されるシーンを指定します
	/// </summary>
	/// <typeparam name="T">ISceneを継承したクラス</typeparam>
	/// <param name="scene">シーンクラスのインスタンス</param>
	template<DerivedIScene T>
	void RegisterBootScene(T scene);
private:
	std::unordered_map<std::type_index, std::shared_ptr<IScene>> _sceneContainer;
	std::unique_ptr<IScene> _currentScene;
};