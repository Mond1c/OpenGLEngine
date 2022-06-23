#include "ICollider.h"

void engine::Components::Colliders::Box::Update() const
{
	for (auto& collider : Colliders) {
		if (collider.get() == this) continue;
		if (DetectCollision(this, collider.get())) {
			std::cout << 234 << std::endl;
		}
	}
}
