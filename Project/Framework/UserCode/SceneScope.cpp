#include "SceneSystem/SceneScope.h"

#include <memory>

#include "../../Code/Scene/MockScene.h"

using namespace UtX;

void SceneScope::definer(SceneList& sceneList) {
	// ‚±‚±‚ÅƒQ[ƒ€‚ÌƒV[ƒ“‚ğ“o˜^‚·‚é
	sceneList.registerBootScene<MockScene>(std::make_shared<MockScene>());
}