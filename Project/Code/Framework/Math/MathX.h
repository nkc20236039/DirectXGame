#pragma once
#include "Struct/Vector2.h"
#include <DirectXMath.h>

class MathX final {
public:
	MathX() = default;
	~MathX() = default;

	static float toRadians(float deg);
	static float toDegrees(float rad);
};