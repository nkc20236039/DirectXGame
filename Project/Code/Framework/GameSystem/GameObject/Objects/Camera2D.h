#pragma once
#include "Object.h"
#include "../../../Math/MathX.h"
#include <DirectXMath.h>

class Camera2D : public Object {
public:
	Camera2D(Transform transform, float zoom = 1.0f)
		: transform(transform), zoom(zoom), backgroundColor(Color(0.0f, 0.0f, 0.0f)) {
	}
	~Camera2D() = default;

	DirectX::XMMATRIX getCameraMatrix();
	void setBackgroundColor(Color color);
	Color getBackgourndColor() {
		return backgroundColor;
	}
private:
	Color backgroundColor;
	Transform transform;
	float zoom;
};