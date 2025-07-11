#pragma once
#include <DirectXMath.h>

namespace UtX {
	struct Vector2 {
	public:
		Vector2(float x, float y) : x(x), y(y) {}
		~Vector2() = default;

		float x;
		float y;

		float Length();
		Vector2 Normalize();

		static const Vector2 zero;
		static const Vector2 one;
		static const Vector2 right;
		static const Vector2 up;

		bool operator==(const Vector2& other) const {
			return (x == other.x) && (y == other.y);
		}

		bool operator!=(const Vector2& other) const {
			return (x != other.x) || (y != other.y);
		}
	};
}