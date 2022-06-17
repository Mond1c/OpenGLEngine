#pragma once
#include "Utility.h"

namespace engine {
	class Transform
	{
	public:
		Vector2f Position;
		Vector2f Scale;
	public:
		Transform(Vector2f&& position, Vector2f&& scale) :
			Position(ToScreenPoint(position)), Scale(scale) {}
	};
}

