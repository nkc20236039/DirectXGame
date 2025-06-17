#pragma once
#include "Object.h"
#include "../../../Math/Math.h"
#include <DirectXMath.h>

class Camera2D : public Object {
public:
	Camera2D() = default;
	~Camera2D() = default;

	void SetPosition(Vector2 position);
	void SetRotation(float angle);
	void SetZoom(float scale);

	DirectX::XMMATRIX GetViewProjectionMatrix() const;
};