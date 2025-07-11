#pragma once

#include <string>
#include <array>

#include "GameObject/Objects/Object.h"
#include "Graphics/SpriteMesh.h"
#include "Math/MathX.h"

namespace UtX {
	class Actor : public Object {
	public:
		Actor(std::string spritePath, Transform transform, uint32_t layer)
			: spritePath(spritePath), transform(transform), layer(layer), vertexList{} {
		}
		~Actor() = default;

		// Getter
		std::string getSpritePath() { return spritePath; }
		Transform getTransform() { return transform; }
		uint32_t getLayer() { return layer; }
		std::array<Vertex, 4>& getVertexList() { return vertexList; }

		// Setter
		void setSpritePath(std::string path) { spritePath = path; }
		void setTransform(Transform transform) { Actor::transform = transform; }
		void setLayer(uint32_t number) { layer = number; }
		void setVertexList(std::array<Vertex, 4> vertex) { vertexList = vertex; }
	private:
		std::string spritePath;
		Transform transform;
		uint32_t layer;
		std::array<Vertex, 4> vertexList;
	};
}