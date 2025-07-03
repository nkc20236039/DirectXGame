#pragma once

#include <typeindex>
#include <unordered_map>
#include <string>
#include <memory>

#include "SceneSystem/IScene.h"

namespace UtX {
	// IScene���p�����Ă��邩�̏���
	template <typename T>
	concept DerivedIScene = std::is_base_of<IScene, T>::value;

	class SceneList {
	public:
		SceneList()
			: existBootScene(false), bootSceneIndex(typeid(void)) {
		}
		~SceneList() = default;

		/// <summary>
		/// �V�[�����Q�[���T�C�N���ɓo�^���܂�
		/// </summary>
		/// <typeparam name="T">IScene���p�������N���X</typeparam>
		/// <param name="scene">�V�[���N���X�̃C���X�^���X</param>
		template<DerivedIScene T>
		void registerScene(std::shared_ptr<T> scene) {
			sceneContainer[typeid(T)] = scene;
		}

		/// <summary>
		/// �Q�[���J�n���ŏ��Ɏ��s�����V�[�����w�肵�܂�
		/// </summary>
		/// <typeparam name="T">IScene���p�������N���X</typeparam>
		/// <param name="scene">�V�[���N���X�̃C���X�^���X</param>
		template<DerivedIScene T>
		void registerBootScene(std::shared_ptr<T> scene) {
			registerScene<T>(scene);
			bootSceneIndex = typeid(T);
			existBootScene = true;
		}

		// TODO:: �������牺�̓C���^�[�t�F�[�X�ŃJ�v�Z��������
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