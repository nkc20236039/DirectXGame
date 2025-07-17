#pragma once

#include <memory>
#include <vector>

#include "SceneSystem/IScene.h"
#include "GameObject/Objects/Actor.h"
#include "../../Code/Actors/Player.h"
#include "../../Code/Actors/BackGround.h"
#include "../../Code/Actors/Bullet.h"

class MockScene : public UtX::IScene {
public:
	MockScene() :time(0.0f), shotSpan(0.1f), vertexList{} {}
	~MockScene() = default;

	// Scene�ɕK�v�Ȋ֐�
	void init() override;
	void enter() override;
	void update() override;
	void exit() override;
private:
	float time;	// �o�ߎ���
	float shotSpan;	// �e�����Ԋu
	std::unique_ptr<Player> player;	// �v���C���[�̊Ǘ��N���X
	std::unique_ptr<BackGround> backGround;	// �w�i�̊Ǘ��N���X
	std::vector<std::unique_ptr<Bullet>> bullets;	// �e�̊Ǘ��N���X
	std::array<UtX::Vertex, 4> vertexList;	// �������_���
};