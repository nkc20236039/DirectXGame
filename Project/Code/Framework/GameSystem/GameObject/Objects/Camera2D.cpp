#include "Camera2D.h"

void Camera2D::setPosition(Vector2 position) {
	// Œ»İ‚ÌÀ•W‚É‘ã“ü
	Camera2D::position = position;
}

void Camera2D::setRotation(float angle) {
	// ƒ‰ƒWƒAƒ“‚É•ÏŠ·‚µ‚Ä‰ñ“]‚Ö‘ã“ü
	rotation = MathX::toRadians(angle);
}

void Camera2D::setZoom(float scale) {
	zoom = scale;
}