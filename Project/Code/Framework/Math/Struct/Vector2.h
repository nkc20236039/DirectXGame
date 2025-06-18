#pragma once

struct Vector2 {
public:
	Vector2(float x, float y) : x(x), y(y) {}

	float x;
	float y;
};

const Vector2 zero = Vector2(0, 0);
const Vector2 one = Vector2(1, 1);
const Vector2 right = Vector2(1, 0);
const Vector2 up = Vector2(0, 1);