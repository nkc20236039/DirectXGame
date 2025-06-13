#include "SceneList.h"

template<DerivedIScene T>
void SceneList::registerBootScene(std::shared_ptr<T> scene) {
	registerScene<T>(scene);
	bootSceneIndex = typeid(T);
	hasBootScene = true;
}

template<DerivedIScene T>
void SceneList::registerScene(std::shared_ptr<T> scene) {
	sceneContainer[typeid(T)] = scene;
}

std::shared_ptr<IScene> SceneList::getScene(std::type_index type) {
	return sceneContainer[type];
}

template<DerivedIScene T>
T SceneList::getScene() {
	return getScene(typeid(T));
}

std::type_index SceneList::getBootSceneIndex() {
	return bootSceneIndex;
}

bool SceneList::isBootSceneRegistered() {
	return hasBootScene;
}