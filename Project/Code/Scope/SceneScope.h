#pragma once
#include "../Framework/SceneSystem/SceneList.h"
#include <memory>

class SceneScope {
public:
	SceneScope() {}
	~SceneScope() {}

	void definer(std::shared_ptr<SceneList> sceneList);

private:

};