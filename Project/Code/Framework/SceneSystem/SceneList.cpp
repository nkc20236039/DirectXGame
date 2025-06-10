#include "SceneList.h"

template<DerivedIScene T>
void SceneList::registerBootScene(T scene) {
	scene.init();
}

template<DerivedIScene T>
void SceneList::registerScene(T scene) {
	scene.init();
}

template<DerivedIScene T>
T SceneList::getScene() {

}