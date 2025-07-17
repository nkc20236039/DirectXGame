#include "../../Code/Scene/MockScene.h"

#include <array>

#include "GameObject/GameObject.h"

using namespace UtX;

void MockScene::init() {
	// �������_���
	vertexList[0].position = { -128.0f, -128.0f, 0.0f };
	vertexList[1].position = { -128.0f, 128.0f, 0.0f };
	vertexList[2].position = { 128.0f, -128.0f, 0.0f };
	vertexList[3].position = { 128.0f, 128.0f, 0.0f };

	vertexList[0].uv = { 0.0f, 1.0f };
	vertexList[1].uv = { 0.0f, 0.0f };
	vertexList[2].uv = { 1.0f, 1.0f };
	vertexList[3].uv = { 1.0f, 0.0f };

	for (int32_t i = 0; i < 4; i++) {
		// ���_�̐F
		vertexList[i].color = { 1.0f, 0.0f, 1.0f, 1.0f };
		// �m�[�}���}�b�v
		vertexList[i].normal = { 0.0f, 0.0f, 1.0f };
	}
}

void MockScene::enter() {
	// �J�����̍쐬
	GameObject::getInstance().create2DCamera(Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(1.0f, 1.0f)), 0.5f)
		->setBackgroundColor(Color(0.2f, 0.2f, 0.2f));
	// �w�i�̍쐬(GBackTex.png)
	auto backGroundObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\GBackTex.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(10.0f, 10.0f)), 0);
	// �v���C���[�̍쐬(MyChar.png)
	auto playerObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\MyChar.png", Transform(Vector2(0.0f, 0.0f), 0.0f, Vector2(0.75f, 0.75f)), 2);
	// TODO:: �A�N�^�[�̍X�V�����ɃR���|�[�l���g��ǉ����鏈�����쐬����Update�𓯊�����d�g�݂����
	// �v���C���[�̊Ǘ��N���X
	player = std::make_unique<Player>(playerObject, vertexList);
	// �w�i�̊Ǘ��N���X
	backGround = std::make_unique<BackGround>(backGroundObject, vertexList);
}

void MockScene::update() {
	// ���̃t���[�����Ԃ��v�Z
	float deltaTime = 1.0f / 60.0f;	// �R���p�C�����ɍœK��
	// �v���C���[�̍X�V
	player->Update(deltaTime);
	// �w�i�̍X�V
	backGround->Update(deltaTime);

	// ���Ԃ����Z
	time += deltaTime;

	// �X�y�[�X�L�[��������Ă��āA�e�̔��ˊԊu���o�߂��Ă���ꍇ
	if (GetAsyncKeyState(VK_SPACE) & 0x8000 && shotSpan < time) {
		// �e�̃A�N�^�[���쐬(MyShot.png)
		auto bulletObject = GameObject::getInstance().createActor(".\\Assets\\Sprite\\MyShot.png", Transform(player->GetPosition(), 0.0f, Vector2(0.5f, 0.5f)), 1);
		// �z��ɒe��ǉ�
		bullets.push_back(std::make_unique<Bullet>(bulletObject, vertexList));
		// ���Ԃ�������
		time = 0;
	}

	// �e���Ȃ��ꍇ�͉������Ȃ�
	if (bullets.empty()) { return; }

	// �e�e�̍X�V
	for (auto bullet = bullets.begin(); bullet != bullets.end();) {
		// �e�̎��Ԃ��폜����Ă���ꍇ
		if (!(*bullet)->HasInstance()) {
			bullet = bullets.erase(bullet);	// �e�̊Ǘ��I��
			continue;
		}

		// �e�̍X�V
		(*bullet)->Update(deltaTime);
		bullet++;	// ���̒e��
	}
}

void MockScene::exit() {
}
