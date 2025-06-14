#pragma once
#include "../Framework/SceneSystem/IScene.h"

class MockScene : public IScene {
	// IScene を介して継承されました
	void init() const override;
	void enter() const override;
	void tick() const override;
	void exit() const override;
};