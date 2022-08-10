#include "ICollider.h"

using namespace engine;
using namespace components;

void colliders::Box::Update() {
    for (auto &collider : ALL_COLLIDERS) {
        if (collider.get() == this) continue;
        if (!isCollisionDetected_ && physics_ && DetectCollision(this, collider.get())) {
            Push(collider->GetVelocity(), collider->GetMass());
            //collider->Push(GetVelocity(), GetMass());
            isCollisionDetected_ = true;
            return;
        }
    }
    isCollisionDetected_ = false;
}

core::Transform ICollider::GetTransform() const {
    return *transform_;
}

core::Vector2f ICollider::GetVelocity() const {
    if (!physics_) return core::Vector2f::Zero;
    return physics_->GetVelocity();
}

float ICollider::GetMass() const {
    if (!physics_) return 0.0f;
    return physics_->GetMass();
}

void ICollider::Push(core::Vector2f otherSpeed, float otherMass) {
    if (!physics_) return;
    physics_->Push(otherSpeed, otherMass);
}

void colliders::Circle::Update() {
    for (auto &collider : ALL_COLLIDERS) {
        if (collider.get() == this) continue;
        if (!isCollisionDetected_ && physics_ && DetectCollision(this, collider.get())) {
            Push(collider->GetVelocity(), collider->GetMass());
            isCollisionDetected_ = true;
            return;
        }
    }
    isCollisionDetected_ = false;
}
