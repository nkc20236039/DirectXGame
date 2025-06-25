#pragma once
#include <memory>
#include "IScene.h"
#include "SceneList.h"

class SceneSystem {
public:
	~SceneSystem() {}

	static SceneSystem& getInstance();
	bool init();
	IScene& getCurrentScene();

	template<DerivedIScene T>
	void ChangeScene() {

	}
private:
	SceneSystem();
	static SceneSystem* instance;

	std::unique_ptr<SceneList> sceneList;
	std::shared_ptr<IScene> currentScene;
};