#pragma once
#include "../Framework/SceneSystem/SceneList.h"
#include <memory>

class SceneScope {
public:
	SceneScope() {}
	~SceneScope() {}

	void Definer(std::shared_ptr<SceneList> sceneList);

private:

};