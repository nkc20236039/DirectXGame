#include "../MathX.h"

inline float MathX::toRadians(float deg) {
	return DirectX::XMConvertToRadians(deg);
}

inline float MathX::toDegrees(float rad) {
	return DirectX::XMConvertToDegrees(rad);
}