#pragma once
#include "../../Math/MathX.h"

class Transform {
public:
	Transform(Vector2 position, float angle, Vector2 scale);
	~Transform() = default;

	// Setter
	void setPosition(Vector2 position);
	void setAngle(float angle);
	void setScale(Vector2 scale);

	// Getter
	Vector2 getPosition();
	float getAngle();
	Vector2 getScale();
	DirectX::XMMATRIX getPositionMatrix();
	DirectX::XMMATRIX getRotationMatrix();
	DirectX::XMMATRIX getScaleMatrix();

private:
	Vector2 position;
	float rotation;
	Vector2 scale;
};