#pragma once
#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>
#include "../../Scope/SceneScope.h"
#include "IScene.h"

// IScene���p�����Ă��邩�̏���
template <typename T>
concept DerivedIScene = std::is_base_of<IScene, T>::value;

class SceneList {
public:
	/// <summary>
	/// �V�[�����Q�[���T�C�N���ɓo�^���܂�
	/// </summary>
	/// <typeparam name="T">IScene���p�������N���X</typeparam>
	/// <param name="scene">�V�[���N���X�̃C���X�^���X</param>
	template<DerivedIScene T>
	void registerScene(std::shared_ptr<T> scene);

	/// <summary>
	/// �Q�[���J�n���ŏ��Ɏ��s�����V�[�����w�肵�܂�
	/// </summary>
	/// <typeparam name="T">IScene���p�������N���X</typeparam>
	/// <param name="scene">�V�[���N���X�̃C���X�^���X</param>
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