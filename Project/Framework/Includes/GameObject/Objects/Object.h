#pragma once

#include "GameObject/IBehavior.h"
#include "GameObject/Transform.h"

namespace UtX {
	class Object {
	public:
		Object() = default;
		~Object() = default;

		Object AddBehavior(IBehavior& behavior);

	private:

	};
}