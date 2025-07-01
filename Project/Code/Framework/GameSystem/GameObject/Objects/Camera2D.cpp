#include "Camera2D.h"
#include "../../../ApplicationConfig.h"
using namespace DirectX;

XMMATRIX Camera2D::getCameraMatrix() {
	// 普通のtransformとは逆のためここで行列変換をする
	Vector2 position = transform.getPosition();
	// ビュー行列を求める
	XMMATRIX view
		= XMMatrixScaling(1.0f, 1.0f, 1.0f)
		* XMMatrixRotationZ(-transform.getAngle())
		* XMMatrixTranslation(-position.x, -position.y, 0.0f);

	// 画面の真ん中を求める
	float halfWidth = (WINDOW_WIDTH * 0.5f) / zoom;
	float halfHeight = (WINDOW_HEIGHT * 0.5f) / zoom;
	// プロジェクション行列を求める
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