#include "Transform.h"
using namespace DirectX;

Transform::Transform(Vector2 position, float angle, Vector2 scale) : position(position), scale(scale) {
	rotation = MathX::toRadians(angle);
}

void Transform::setPosition(Vector2 position) {
	// 現在の座標に代入
	Transform::position = position;
}

void Transform::setAngle(float angle) {
	// ラジアンに変換して回転へ代入
	rotation = MathX::toRadians(angle);
}

void Transform::setScale(Vector2 scale) {
	// 現在のサイズに代入
	Transform::scale = scale;
}

Vector2 Transform::getPosition() {
	return position;
}

float Transform::getAngle() {
	return MathX::toDegrees(rotation);
}

Vector2 Transform::getScale() {
	return scale;
}

XMMATRIX Transform::getPositionMatrix() {
	return XMMatrixTranslation(position.x, position.y, 0.0f);
}

XMMATRIX Transform::getRotationMatrix() {
	return XMMatrixRotationZ(rotation);
}

XMMATRIX Transform::getScaleMatrix() {
	return XMMatrixScaling(scale.x, scale.y, 1.0f);
}