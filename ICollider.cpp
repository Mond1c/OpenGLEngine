#include "ICollider.h"

void engine::Components::Colliders::Box::Update() const
{
	//std::cout << ALL_COLLIDERS.size() << std::endl;
	for (auto& collider : ALL_COLLIDERS) {
		if (collider.get() == this) continue;
		if (DetectCollision(this, collider.get())) {
			std::cout << 234 << std::endl;
			//ALL_COLLISIONS[this] = collider;
		}
	}
}
