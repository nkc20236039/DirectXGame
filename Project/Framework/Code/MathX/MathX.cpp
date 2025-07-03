#include "Math/MathX.h"

using namespace UtX;

float MathX::toRadians(float deg) {
	return DirectX::XMConvertToRadians(deg);
}

float MathX::toDegrees(float rad) {
	return DirectX::XMConvertToDegrees(rad);
}