#include "Transform.h"
using namespace DirectX;

Transform::Transform(Vector2 position, float angle, Vector2 scale) : position(position), scale(scale) {
	rotation = MathX::toRadians(angle);
}

void Transform::setPosition(Vector2 position) {
	// ���݂̍��W�ɑ��
	Transform::position = position;
}

void Transform::setAngle(float angle) {
	// ���W�A���ɕϊ����ĉ�]�֑��
	rotation = MathX::toRadians(angle);
}

void Transform::setScale(Vector2 scale) {
	// ���݂̃T�C�Y�ɑ��
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