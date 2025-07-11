#pragma once

#include <memory>

#include "SceneSystem/IScene.h"
#include "GameObject/Objects/Actor.h"
#include "../../Code/Actors/Player.h"

class MockScene : public UtX::IScene {
public:
	MockScene() :time(0.0f), vertexList{} {}
	~MockScene() = default;

	// IScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void init() override;
	void enter() override;
	void update() override;
	void exit() override;
private:
	float time;
	std::shared_ptr<Player> player;
	std::shared_ptr<UtX::Actor> backGround;
	std::array<UtX::Vertex, 4> vertexList;
};