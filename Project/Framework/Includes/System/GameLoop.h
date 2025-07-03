#pragma once
#include <memory>
#include "SceneSystem/SceneSystem.h"
#include "System/DirectXApplication.h"

namespace UtX {
	class GameLoop {
	public:
		bool init(DirectXApplication& graphicApp);
		void update();
	};
}