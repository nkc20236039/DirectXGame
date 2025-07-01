#include "Camera2D.h"
#include "../../../ApplicationConfig.h"
using namespace DirectX;

XMMATRIX Camera2D::getCameraMatrix() {
	// ���ʂ�transform�Ƃ͋t�̂��߂����ōs��ϊ�������
	Vector2 position = transform.getPosition();
	// �r���[�s������߂�
	XMMATRIX view
		= XMMatrixScaling(1.0f, 1.0f, 1.0f)
		* XMMatrixRotationZ(-transform.getAngle())
		* XMMatrixTranslation(-position.x, -position.y, 0.0f);

	// ��ʂ̐^�񒆂����߂�
	float halfWidth = (WINDOW_WIDTH * 0.5f) / zoom;
	float halfHeight = (WINDOW_HEIGHT * 0.5f) / zoom;
	// �v���W�F�N�V�����s������߂�
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(
		-halfWidth,
		halfWidth,
		-halfHeight,
		halfHeight,
		0.0f, 1.0f
	);

	return view * projection;
}

void Camera2D::setBackgroundColor(Color color) {
	backgroundColor = color;
}