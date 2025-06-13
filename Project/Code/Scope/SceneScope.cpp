#include "SceneScope.h"
#include "../Scene/MockScene.h"

void SceneScope::definer(SceneList& sceneList) {
	// ‚±‚±‚ÅƒQ[ƒ€‚ÌƒV[ƒ“‚ğ“o˜^‚·‚é
	sceneList.registerBootScene<MockScene>(std::make_shared<MockScene>());
}