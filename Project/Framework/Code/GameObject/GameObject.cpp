#include "GameObject/GameObject.h"

using namespace DirectX;
using namespace UtX;

// ������
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
		// TODO:: �G���[�����N���X�Ɉړ�
		throw "[GameObject]�͏���������Ă��܂���";
	}

	return *instance;
}

std::shared_ptr<Camera2D> GameObject::create2DCamera(Transform transform, float zoom) {
	// �J�������쐬
	mainCamera = std::make_shared<Camera2D>(transform, zoom);

	return mainCamera;
}

std::shared_ptr<Actor> GameObject::createActor(std::string spritePath, Transform transform, uint32_t layer) {
	// �V�����A�N�^�[���쐬����
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(spritePath, transform, layer);

	// �����_�����O����ʒu���݂��Ĕz�u
	std::list<std::shared_ptr<Actor>>::iterator actorIterator;
	for (actorIterator = actors.begin(); actorIterator != actors.end(); actorIterator++) {
		// ���C���[�̗D��x���w�肳�ꂽ�D��x�ɂȂ�܂ő�������
		if (layer < (*actorIterator)->getLayer()) {
			break;	// �������������Ń��[�v�𔲂��A���݂�iterator�̕����ɂ��Ƃő}������
		}
	}

	// ���X�g�̎w��ʒu�֑}������
	actors.insert(actorIterator, newActor);

	return newActor;
}

void GameObject::update() {
	// �A�N�^�[�����Ȃ��ꍇ�͉������Ȃ�
	if (actors.empty()) { return; }

	// �e�A�N�^�[�̍X�V�������Ăяo��
	for (auto actor = actors.begin(); actor != actors.end();) {
		for (auto behavior : (*actor)->GetBehavior()) {
			behavior->Update();
		}

		// �A�N�^�[���Ǘ����Ă���N���X�����X�g�����������ꍇ
		if (actor->use_count() == 1) {
			actor = actors.erase(actor);	// �A�N�^�[���폜
			continue;
		}

		actor++;
	}
}

void GameObject::render() {
	// �r���[�̃N���A
	application.clearView(mainCamera->getBackgourndColor().getRawColor());

	for (auto actor : actors) {
		// �I�u�W�F�N�g�̍��W���J�����ɍ��킹��world/view/projection�s��ɕϊ�
		XMMATRIX wvp
			= actor->getTransform().getScaleMatrix()
			* actor->getTransform().getRotationMatrix()
			* actor->getTransform().getPositionMatrix()
			* mainCamera->getCameraMatrix();

		// �I�u�W�F�N�g�̃����_�����O
		spriteMesh->rendering(wvp, spriteRenderer->getSprite(actor->getSpritePath()), actor->getVertexList());
	}
	// �`��̏I������
	application.present();
}

/* �C���X�^���X��������p���� */
bool GameObject::init(DirectXApplication& app) {
	// �V���O���g���p�C���X�^���X���o�^����Ă��Ȃ��ꍇ
	if (!instance) {
		// �V�����쐬����
		instance = new GameObject(app);	// �i�v�����̂��ߐ��|�C���^�ŊǗ�
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
		".\\Assets\\Sprite\\ErrorTexture.png");
	if (!isComplete) { return false; }

	instance->spriteMesh->init(shaderResource);

	return true;
}