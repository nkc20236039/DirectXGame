#include "GameObject.h"

GameObject::GameObject(DirectXApplication& app)
	: application(app), isInitialized(true) {
}

GameObject* GameObject::instance = nullptr;

/// <summary>
/// �Q�[���I�u�W�F�N�g�N���X�̒P��C���X�^���X���擾���܂�
/// </summary>
/// <returns></returns>
GameObject& GameObject::getInstance() {
	// �C���X�^���X�����݂��Ȃ���������������Ă��Ȃ��ꍇ
	if (!instance || !instance->isInitialized) {
		// �G���[���o��
		throw "[GameObject]�͏���������Ă��܂���";
	}

	return *instance;
}

std::shared_ptr<Camera2D> GameObject::create2DCamera() {

}

std::shared_ptr<Actor> GameObject::createActor(std::string spritePath, Transform transform, uint32_t layer) {
	// �V�����A�N�^�[���쐬����
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(spritePath, transform, layer);

	// �����_�����O����ʒu���݂��Ĕz�u
	std::list<std::shared_ptr<Actor>>::iterator actorIterator;
	for (actorIterator = actors.begin(); actorIterator != actors.end(); actorIterator++) {
		// ���C���[�̗D��x���w�肳�ꂽ�D��x�ɂȂ�܂ő�������
		if (layer < actorIterator->get()->getLayer()) {
			break;	// �������������Ń��[�v�𔲂��A���݂�iterator�̕����ɂ��Ƃő}������
		}
	}

	// ���X�g�̎w��ʒu�֑}������
	actors.insert(actorIterator, newActor);

	return newActor;
}

void GameObject::render() {

}

/* �C���X�^���X��������p���� */
bool GameObject::init(DirectXApplication& app) {
	// �V���O���g���p�C���X�^���X���o�^����Ă��Ȃ��ꍇ
	if (!instance) {
		// �V�����쐬����
		instance = new GameObject(app);	// �i�v�����̂��ߐ��|�C���^�ŊǗ�()
	}

	// �쐬�����C���X�^���X�֕`��ɕK�v�ȃN���X�̃|�C���^���쐬
	instance->shader = std::make_unique<Shader>(app);
	instance->spriteMesh = std::make_unique<SpriteMesh>(app);
	instance->spriteRenderer = std::make_unique<SpriteRenderer>(app);

	// StandardShaderResource���擾
	std::shared_ptr<ShaderResource> shaderResource = std::make_shared<ShaderResource>();
	// �����V�F�[�_�[���쐬
	bool isComplete = instance->shader->CreateStandardShader(
		".\\Assets\\Shader\\Standard\\VertexShader.hlsl",
		".\\Assets\\Shader\\Standard\\PixelShader.hlsl",
		shaderResource);
	// �����������s�����炱�̏������֐������s�Ƃ��ĕԂ�
	if (!isComplete) { return false; }

	isComplete = instance->spriteRenderer->createStandardSprite(
		".\\Assets\\Sprite\\ColorfulSprite.png");
	if (!isComplete) { return false; }

	instance->spriteMesh->init(shaderResource);

	return true;
}