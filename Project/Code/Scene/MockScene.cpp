#include "../../Code/Scene/MockScene.h"
#include "GameObject/GameObject.h"

void MockScene::init() const {
}

void MockScene::enter() const {
	GameObject::getInstance().create2DCamera(Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 100)
		->setBackgroundColor(Color(0.2f, 0.2f, 0.2f));
	GameObject::getInstance().createActor(".\\Assets\\Sprite\\DirectX.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0);
}

void MockScene::update() const {

}

void MockScene::exit() const {
}
