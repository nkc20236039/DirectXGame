#pragma once
#include "../Framework/SceneSystem/IScene.h"

class MockScene : public IScene {
	// IScene ����Čp������܂���
	void init() const override;
	void enter() const override;
	void tick() const override;
	void exit() const override;
};