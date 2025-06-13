#pragma once
#include "../Framework/SceneSystem/IScene.h"

class MockScene : public IScene {
	// IScene ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	void init() const override;
	void enter() const override;
	void tick() const override;
	void exit() const override;
};