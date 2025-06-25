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