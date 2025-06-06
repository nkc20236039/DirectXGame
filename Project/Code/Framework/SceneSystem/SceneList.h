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
	void Register(T scene);

	/// <summary>
	/// �Q�[���J�n���ŏ��Ɏ��s�����V�[�����w�肵�܂�
	/// </summary>
	/// <typeparam name="T">IScene���p�������N���X</typeparam>
	/// <param name="scene">�V�[���N���X�̃C���X�^���X</param>
	template<DerivedIScene T>
	void RegisterBootScene(T scene);
private:
	std::unordered_map<std::type_index, std::shared_ptr<IScene>> _sceneContainer;
	std::unique_ptr<IScene> _currentScene;
};