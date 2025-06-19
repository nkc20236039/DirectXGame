#pragma once
#include "Object.h"
#include "../../../Math/MathX.h"
#include <DirectXMath.h>

class Camera2D : public Object {
public:
	Camera2D(Transform transform, float zoom = 1.0f) : transform(transform), zoom(zoom) {}
	~Camera2D() = default;

	DirectX::XMMATRIX getCameraMatrix();
private:
	Transform transform;
	float zoom;
};