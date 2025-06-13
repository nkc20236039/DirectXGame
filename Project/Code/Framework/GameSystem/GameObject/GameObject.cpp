#include "GameObject.h"

/// <summary>
/// �Q�[���I�u�W�F�N�g�N���X�̒P��C���X�^���X���擾���܂�
/// </summary>
/// <returns></returns>
GameObject& GameObject::GetInstance() {
	// static�ōŏ��̈�񂾂��C���X�^���X���쐬
	static GameObject instance;
	// �쐬���ꂽ�C���X�^���X��Ԃ�
	return instance;
}

std::shared_ptr<Actor> GameObject::CreateActor(std::string spritePath, Vector2 position, Vector2 scale, Quaternion rotation, uint32_t layer) {
	// �V�����A�N�^�[���쐬����
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(spritePath, position, scale, rotation, layer);

	// �����_�����O����ʒu���݂��Ĕz�u
	std::list<std::shared_ptr<Actor>>::iterator actorIterator;
	for (actorIterator = actors.begin(); actorIterator != actors.end(); actorIterator++) {
		// ���C���[�̗D��x���w�肳�ꂽ�D��x�ɂȂ�܂ő�������
		if (layer < actorIterator->get()->GetLayer()) {
			break;
		}
	}

	// ���X�g�̎w��ʒu�֑}������
	actors.insert(actorIterator, newActor);

	return newActor;
}

void GameObject::Render() {
	
}