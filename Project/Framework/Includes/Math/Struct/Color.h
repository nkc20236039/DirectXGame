#pragma once
#include <algorithm>

namespace UtX {
	struct Color {
	public:
		float r, g, b, a;

		Color(float r, float g, float b, float a) {
			Color::r = std::clamp(r, 0.0f, 1.0f);
			Color::g = std::clamp(g, 0.0f, 1.0f);
			Color::b = std::clamp(b, 0.0f, 1.0f);
			Color::a = std::clamp(a, 0.0f, 1.0f);
		}
		// 不透明想定のコンストラクタ
		Color(float r, float g, float b) {
			Color::r = std::clamp(r, 0.0f, 1.0f);
			Color::g = std::clamp(g, 0.0f, 1.0f);
			Color::b = std::clamp(b, 0.0f, 1.0f);
			a = 1;
		}

		DirectX::XMVECTORF32 getRawColor() {
			return { r, g, b, a };
		}
	};
}