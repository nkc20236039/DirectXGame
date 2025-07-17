#include "../../Code/Actors/BackGround.h"

using namespace UtX;

void BackGround::Update(float deltaTime) {
	// �w�i�p�̒��_���
	std::array<Vertex, 4> backGroundVertexList = vertexList;

	// UV.y�����Z��������UV�X�N���[��������
	uv.y += deltaTime * animationTime;

	// ���X�g�ɓo�^
	backGroundVertexList[0].uv = { uv.x, uv.y + 1 };
	backGroundVertexList[1].uv = { uv.x, uv.y };
	backGroundVertexList[2].uv = { uv.x + 1, uv.y + 1 };
	backGroundVertexList[3].uv = { uv.x + 1, uv.y };

	backGround->setVertexList(backGroundVertexList);
}