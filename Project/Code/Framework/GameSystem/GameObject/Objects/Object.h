#pragma once
#include "../IBehavior.h"

class Object {
public:
	Object() = default;
	~Object() = default;

	Object AddBehavior(IBehavior& behavior);

private:

};