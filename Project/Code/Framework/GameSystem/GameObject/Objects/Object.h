#pragma once
#include "../IBehavior.h"
#include "../Transform.h"

class Object {
public:
	Object() = default;
	~Object() = default;

	Object AddBehavior(IBehavior& behavior);

private:

};