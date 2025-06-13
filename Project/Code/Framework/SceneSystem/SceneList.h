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
	void registerScene(std::shared_ptr<T> scene);

	/// <summary>
	/// ゲーム開始時最初に実行されるシーンを指定します
	/// </summary>
	/// <typeparam name="T">ISceneを継承したクラス</typeparam>
	/// <param name="scene">シーンクラスのインスタンス</param>
	template<DerivedIScene T>
	void registerBootScene(std::shared_ptr<T> scene);


	std::shared_ptr<IScene> getScene(std::type_index type);

	template<DerivedIScene T>
	T getScene();

	bool isBootSceneRegistered();
	std::type_index getBootSceneIndex();
private:
	bool hasBootScene;
	std::type_index bootSceneIndex;
	std::unordered_map<std::type_index, std::shared_ptr<IScene>> sceneContainer = {};
};