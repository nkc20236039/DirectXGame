#pragma once

#include <vector>
#include <memory>

#include "GameObject/IBehavior.h"
#include "GameObject/Transform.h"

namespace UtX {
	// IBehavior‚ğŒp³‚µ‚Ä‚¢‚é‚©‚ÌğŒ
	template <typename T>
	concept DerivedIBehavior = std::is_base_of<IBehavior, T>::value;
	
	class Object {
	public:
		Object() = default;
		~Object() = default;

		template<DerivedIBehavior T, typename... Args>
		std::shared_ptr<IBehavior> AddBehavior(Args&&... args) {
			std::shared_ptr<IBehavior> newBehavior = std::make_shared<T>(args);
			behaviors.push_back(newBehavior);

			return newBehavior;
		}

		std::vector<std::shared_ptr<IBehavior>> GetBehavior() { return behaviors; }
	private:
		std::vector<std::shared_ptr<IBehavior>> behaviors;
	};
}