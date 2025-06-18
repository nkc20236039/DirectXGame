#pragma once
#include "Object.h"
#include "../../../Math/MathX.h"
#include <DirectXMath.h>

class Camera2D : public Object {
public:
	Camera2D() = default;
	~Camera2D() = default;

	void setPosition(Vector2 position);
	void setRotation(float angle);
	void setZoom(float scale);

	Vector2 getPosition();
	float getRotation();
	float getZoom();

	DirectX::XMMATRIX getViewProjectionMatrix() const;
private:
	Vector2 position;
	float rotation;
	float zoom = 1.0f;
};