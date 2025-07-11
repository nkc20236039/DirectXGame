#pragma once

namespace UtX {
	class IScene {
	public:
		virtual ~IScene() = default;
		virtual void init() = 0;
		virtual void enter() = 0;
		virtual void update() = 0;
		virtual void exit() = 0;
	};
}