#pragma once
#include "Utility.h"

namespace engine::core {
	class Transform
	{
	public:
		Vector2f Position;
		Vector2f Scale;
	public:
		Transform(const Vector2f& position, const Vector2f& scale) :
			Position(ToScreenPoint(position)), Scale(scale) {}
	public:
		void Translate(const Vector2f& vec) {
			Position += ToScreenPoint(vec);
		}
	};
}

