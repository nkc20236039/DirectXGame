#include "MockScene.h"
#include "../Framework/GameSystem/GameObject/GameObject.h"

void MockScene::init() const {
}

void MockScene::enter() const {
	GameObject::getInstance().create2DCamera();
	GameObject::getInstance().createActor();
}

void MockScene::update() const {

}

void MockScene::exit() const {
}
