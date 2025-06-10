#pragma once
#include <memory>
#include "IScene.h"
#include "SceneList.h"

class SceneSystem {
public:
	SceneSystem();
	~SceneSystem() {}

	bool Init();
	IScene& GetCurrentScene();

	template<DerivedIScene T>
	static void ChangeScene();
private:
	std::unique_ptr<SceneList> sceneList;
	std::unique_ptr<IScene> currentScene;
};