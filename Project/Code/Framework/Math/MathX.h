#pragma once
#include "Struct/Vector2.h"
#include <DirectXMath.h>

class MathX final
{
public:
	MathX() = default;
	~MathX() = default;

	static inline float toRadians(float deg);
	static inline float toDegrees(float rad);
};