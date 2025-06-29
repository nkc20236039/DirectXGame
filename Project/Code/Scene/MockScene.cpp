#include "MockScene.h"
#include "../Framework/GameSystem/GameObject/GameObject.h"

void MockScene::init() const {
}

void MockScene::enter() const {
	GameObject::getInstance().create2DCamera(Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)));
	GameObject::getInstance().createActor(".\\Assets\\Sprite\\ColorfulSprite.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0);
}

void MockScene::update() const {

}

void MockScene::exit() const {
}
