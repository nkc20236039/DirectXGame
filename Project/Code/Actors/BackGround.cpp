#include "../../Code/Actors/BackGround.h"

using namespace UtX;

void BackGround::Update(float deltaTime) {
	// ”wŒi—p‚Ì’¸“_î•ñ
	std::array<Vertex, 4> backGroundVertexList = vertexList;

	// UV.y‚ğ‰ÁZ‚µ‘±‚¯‚ÄUVƒXƒNƒ[ƒ‹‚ğ‚·‚é
	uv.y += deltaTime * animationTime;

	// ƒŠƒXƒg‚É“o˜^
	backGroundVertexList[0].uv = { uv.x, uv.y + 1 };
	backGroundVertexList[1].uv = { uv.x, uv.y };
	backGroundVertexList[2].uv = { uv.x + 1, uv.y + 1 };
	backGroundVertexList[3].uv = { uv.x + 1, uv.y };

	backGround->setVertexList(backGroundVertexList);
}