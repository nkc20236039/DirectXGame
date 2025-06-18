#pragma once
#include "Object.h"
#include "../../../Math/MathX.h"
#include <string>

class Actor : public Object{
public:
	Actor(std::string spritePath, Vector2 position, Vector2 scale, Quaternion rotation, uint32_t layer)
		: spritePath(spritePath), position(position), scale(scale), rotation(rotation), layer(layer) {
	}
	~Actor() = default;

	std::string GetSpritePath() { return spritePath; }
	Vector2 GetPosition() { return position; }
	Vector2 GetScale() { return scale; }
	Quaternion GetRotation() { return rotation; }
	uint32_t GetLayer() { return layer; }
private:
	std::string spritePath;
	Vector2 position;
	Vector2 scale;
	Quaternion rotation;
	uint32_t layer;
};