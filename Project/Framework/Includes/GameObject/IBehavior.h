#pragma once

namespace UtX {
	class IBehavior {
	public:
		IBehavior() = default;
		~IBehavior() = default;
		virtual void Start() const = 0;
		virtual void Update() const = 0;
		virtual void OnDestroy() const = 0;
	};
}