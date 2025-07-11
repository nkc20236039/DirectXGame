#include "../../Code/Actors/Player.h"

using namespace UtX;

void Player::Update(float deltaTime) {
	Vector2 input = Vector2::zero;
	// ���̓`�F�b�N
	if (GetAsyncKeyState(VK_UP) & 0x8000) {		// ��
		input.y = 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {	// ��
		input.y = -1.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {	// �E
		uv.y = 1;
		input.x = 1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {	// ��
		uv.y = 2;
		input.x = -1.0f;
	}
	// ���͂��Ȃ��ꍇ�A�j���[�V������ҋ@��Ԃɂ���
	if (input == Vector2::zero) {
		uv.y = 0;
	}
	else {	// ���͂�����Ƃ��͈ړ�
		// �m�[�}���C�Y
		input = input.Normalize();

		// �ړ�
		Transform transform = player->getTransform();
		Vector2 position = transform.getPosition();
		position.x = position.x + input.x * speed;
		position.y = position.y + input.y * speed;
		transform.setPosition(position);
		player->setTransform(transform);
	}

	// �X�v���C�g����
	Vector2 uvSplit = Vector2(1.0f / 4.0f, 1.0f / 4.0f);

	time += deltaTime;

	// �v���C���[�̒��_���
	std::array<Vertex, 4> playerVertexList = vertexList;

	if (animationTime <= time) {
		uv.x = (int)(uv.x + 1) % 4;

		time = 0.0f;
	}
	// �v���C���[�̃A�j���[�V����
	float uvX = uvSplit.x * uv.x;
	float uvY = uvSplit.y * uv.y;

	playerVertexList[0].uv = { uvX, uvY + uvSplit.y };
	playerVertexList[1].uv = { uvX, uvY };
	playerVertexList[2].uv = { uvX + uvSplit.x, uvY + uvSplit.y };
	playerVertexList[3].uv = { uvX + uvSplit.x, uvY };

	player->setVertexList(playerVertexList);
}