#include "Physics.h"
#include "Settings.h"
#include "Debug.h"
#include <cassert>

using namespace engine;
using namespace components;

void Physics::Update() {
    if (isGravityEnabled_) transform_->Position += core::ToScreenPoint(core::Vector2f(0, GRAVITY));
    transform_->Position += ToScreenPoint(velocity_);
}

float engine::components::Physics::GetMass() const {
    return mass_;
}

core::Vector2f Physics::GetVelocity() const {
    return velocity_;
}

void Physics::SetVelocity(const core::Vector2f &velocity) {
    velocity_ = velocity;
}

void Physics::EnableGravity() {
    isGravityEnabled_ = true;
}

void Physics::DisableGravity() {
    isGravityEnabled_ = false;
}

void Physics::Push(const core::Vector2f &otherSpeed, float otherMass) {
    float cur_speed = velocity_.Magnitude();
    float other_speed = otherSpeed.Magnitude();
    float new_speed = abs(((mass_ - otherMass) * cur_speed + 2 * otherMass * other_speed) / (mass_ + otherMass));
    core::Vector2f direction = velocity_.Normolize();
    direction *= -1.0f;
    velocity_ = direction * new_speed;
    assert(velocity_ != core::Vector2f::Zero);
}
