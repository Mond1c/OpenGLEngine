#include "ICollider.h"

void engine::components::colliders::Box::Update()
{
	for (auto& collider : ALL_COLLIDERS) {
		if (collider.get() == this) continue;
		if (physics_ && DetectCollision(this, collider.get())) {
			Push(collider->GetVelocity(), collider->GetMass());
			collider->Push(GetVelocity(), GetMass());
		}
	}
}

engine::Transform engine::components::ICollider::GetTransform() const
{
	return *transform_;
}

engine::Vector2f engine::components::ICollider::GetVelocity() const
{
	if (!physics_) return Vector2f::Zero;
	return physics_->GetVelocity();
}

float engine::components::ICollider::GetMass() const
{
	if (!physics_) return 0.0f;
	return physics_->GetMass();
}

void engine::components::ICollider::Push(engine::Vector2f otherSpeed, float otherMass)
{
	if (!physics_) return;
	physics_->Push(otherSpeed, otherMass);
}

void engine::components::colliders::Circle::Update()
{
	for (auto& collider : ALL_COLLIDERS) {
		if (collider.get() == this) continue;
		if (physics_ && DetectCollision(this, collider.get())) {
			Push(collider->GetVelocity(), collider->GetMass());
			collider->Push(GetVelocity(), GetMass());
		}
	}
}
