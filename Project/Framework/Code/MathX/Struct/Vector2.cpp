#include "Math/Struct/Vector2.h"

#include <cmath>

using namespace DirectX;
using namespace UtX;

float Vector2::Length() {
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::Normalize() {
	float length = Length();
	return Vector2(x / length, y / length);
}

const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
const Vector2 Vector2::right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::up = Vector2(0.0f, 1.0f);