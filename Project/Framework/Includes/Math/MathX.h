#pragma once
#include <DirectXMath.h>

#include "Math/Struct/Color.h"
#include "Math/Struct/Vector2.h"

namespace UtX {
	class MathX final {
	public:
		MathX() = default;
		~MathX() = default;

		static float toRadians(float deg);
		static float toDegrees(float rad);
	};
}