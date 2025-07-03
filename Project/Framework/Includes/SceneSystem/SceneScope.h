#pragma once
#include "SceneSystem/SceneList.h"

class SceneScope {
public:
	SceneScope() {}
	~SceneScope() {}

	void definer(UtX::SceneList& sceneList);
};