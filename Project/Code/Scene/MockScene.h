#pragma once
#include "SceneSystem/IScene.h"

using namespace UtX;

class MockScene : public IScene {
	// IScene ����Čp������܂���
	void init() const override;
	void enter() const override;
	void update() const override;
	void exit() const override;
};