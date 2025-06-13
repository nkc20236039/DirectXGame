#include "GameObject.h"

/// <summary>
/// ゲームオブジェクトクラスの単一インスタンスを取得します
/// </summary>
/// <returns></returns>
GameObject& GameObject::GetInstance() {
	// staticで最初の一回だけインスタンスを作成
	static GameObject instance;
	// 作成されたインスタンスを返す
	return instance;
}

std::shared_ptr<Actor> GameObject::CreateActor(std::string spritePath, Vector2 position, Vector2 scale, Quaternion rotation, uint32_t layer) {
	// 新しいアクターを作成する
	std::shared_ptr<Actor> newActor = std::make_shared<Actor>(spritePath, position, scale, rotation, layer);

	// レンダリングする位置をみつけて配置
	std::list<std::shared_ptr<Actor>>::iterator actorIterator;
	for (actorIterator = actors.begin(); actorIterator != actors.end(); actorIterator++) {
		// レイヤーの優先度が指定された優先度になるまで走査する
		if (layer < actorIterator->get()->GetLayer()) {
			break;
		}
	}

	// リストの指定位置へ挿入する
	actors.insert(actorIterator, newActor);

	return newActor;
}

void GameObject::Render() {
	
}