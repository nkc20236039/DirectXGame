#include "Camera2D.h"

void Camera2D::setPosition(Vector2 position) {
	// ���݂̍��W�ɑ��
	Camera2D::position = position;
}

void Camera2D::setRotation(float angle) {
	// ���W�A���ɕϊ����ĉ�]�֑��
	rotation = MathX::toRadians(angle);
}

void Camera2D::setZoom(float scale) {
	zoom = scale;
}