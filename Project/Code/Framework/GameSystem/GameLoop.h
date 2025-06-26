#pragma once
#include <memory>
#include "../SceneSystem/SceneSystem.h"
#include "../Graphics/DirectXApplication.h"

class GameLoop {
public:
	bool init(DirectXApplication& graphicApp);
	void update();
private:
};