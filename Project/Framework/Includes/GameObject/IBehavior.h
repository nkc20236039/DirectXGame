#pragma once

namespace UtX {
	class IBehavior {
	public:
		~IBehavior() = default;
		virtual void Start();
		virtual void Update();
		virtual void OnDestroy() {}
	};
}