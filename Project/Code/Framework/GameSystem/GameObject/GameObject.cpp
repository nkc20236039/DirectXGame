#include "GameObject.h"

GameObject::GameObject(DirectXApplication& app)
	: application(app), isInitialized(true) {
}

GameObject* GameObject::instance = nullptr;

/// <summary>
/// ゲームオブジェクトクラスの単一インスタンスを取得します
/// </summary>
/// <returns></returns>
GameObject& GameObject::getInstance() {
	// インスタンスが存在しないか初期化がされていない場合
	if (!instance || !instance->isInitialized) {
		// エラーを出力
		throw "[GameObject]は初期化されていません";
	}

	return *instance;
}

std::shared_ptr<Camera2D> GameObject::create2DCamera() {

}

std::shared_ptr<Actor> GameObject::createActor(std::string spritePath, Transform transform, uint32_t layer) {
	// 新しいアクターを作成する
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(spritePath, transform, layer);

	// レンダリングする位置をみつけて配置
	std::list<std::shared_ptr<Actor>>::iterator actorIterator;
	for (actorIterator = actors.begin(); actorIterator != actors.end(); actorIterator++) {
		// レイヤーの優先度が指定された優先度になるまで走査する
		if (layer < actorIterator->get()->getLayer()) {
			break;	// 見つかった部分でループを抜け、現在のiteratorの部分にあとで挿入する
		}
	}

	// リストの指定位置へ挿入する
	actors.insert(actorIterator, newActor);

	return newActor;
}

void GameObject::render() {

}

/* インスタンス初期化専用処理 */
bool GameObject::init(DirectXApplication& app) {
	// シングルトン用インスタンスが登録されていない場合
	if (!instance) {
		// 新しく作成する
		instance = new GameObject(app);	// 永久生存のため生ポインタで管理()
	}

	// 作成したインスタンスへ描画に必要なクラスのポインタを作成
	instance->shader = std::make_unique<Shader>(app);
	instance->spriteMesh = std::make_unique<SpriteMesh>(app);
	instance->spriteRenderer = std::make_unique<SpriteRenderer>(app);

	// StandardShaderResourceを取得
	std::shared_ptr<ShaderResource> shaderResource = std::make_shared<ShaderResource>();
	// 初期シェーダーを作成
	bool isComplete = instance->shader->CreateStandardShader(
		".\\Assets\\Shader\\Standard\\VertexShader.hlsl",
		".\\Assets\\Shader\\Standard\\PixelShader.hlsl",
		shaderResource);
	// 初期化が失敗したらこの初期化関数も失敗として返す
	if (!isComplete) { return false; }

	isComplete = instance->spriteRenderer->createStandardSprite(
		".\\Assets\\Sprite\\ColorfulSprite.png");
	if (!isComplete) { return false; }

	instance->spriteMesh->init(shaderResource);

	return true;
}