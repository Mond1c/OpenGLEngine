#include "Physics.h"
#include "Settings.h"

void engine::Components::Physics::Update() const
{
	transform_->Position += engine::ToScreenPoint(engine::Vector2f(0, GRAVITY));
}
