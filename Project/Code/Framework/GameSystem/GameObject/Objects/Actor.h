#pragma once
#include "Object.h"
#include "../../../Math/MathX.h"
#include <string>

class Actor : public Object {
public:
	Actor(std::string spritePath, Transform transform, uint32_t layer)
		: spritePath(spritePath), transform(transform), layer(layer) {
	}
	~Actor() = default;

	// Getter
	std::string getSpritePath() { return spritePath; }
	Transform getTransform() { return transform; }
	uint32_t getLayer() { return layer; }
private:
	std::string spritePath;
	Transform transform;
	uint32_t layer;
};