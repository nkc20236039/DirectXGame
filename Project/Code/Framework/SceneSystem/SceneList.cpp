#include "SceneList.h"

std::shared_ptr<IScene> SceneList::getScene(std::type_index type) {
	return sceneContainer[type];
}

std::type_index SceneList::getBootSceneIndex() {
	return bootSceneIndex;
}

bool SceneList::isBootSceneRegistered() {
	return existBootScene;
}

std::vector<std::shared_ptr<IScene>> SceneList::getAllScenes() {
	std::vector<std::shared_ptr<IScene>> scenes;
	scenes.reserve(sceneContainer.size());

	for (const auto& scene : sceneContainer) {
		scenes.push_back(scene.second);
	}

	return scenes;
}