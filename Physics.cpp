#include "Physics.h"
#include "Settings.h"
#include "Debug.h"

void engine::components::Physics::Update()
{
	if (isGravityEnabled_) transform_->Position += engine::ToScreenPoint(engine::Vector2f(0, GRAVITY));
	transform_->Position += engine::ToScreenPoint(velocity_);
}

float engine::components::Physics::GetMass() const
{
	return mass_;
}

engine::Vector2f engine::components::Physics::GetVelocity() const
{
	return velocity_;
}

void engine::components::Physics::SetVelocity(const Vector2f& velocity)
{
	velocity_ = velocity;
}

void engine::components::Physics::EnableGravity()
{
	isGravityEnabled_ = true;
}

void engine::components::Physics::DisableGravity()
{
	isGravityEnabled_ = false;
}

void engine::components::Physics::Push(const Vector2f& otherSpeed, float otherMass)
{
	float cur_speed = velocity_.Magnitude();
	float other_speed = otherSpeed.Magnitude();
	float new_speed = abs(((mass_ - otherMass) * cur_speed + 2 * otherMass * other_speed) / (mass_ + otherMass));  
	Vector2f direction = velocity_.Normolize();
	direction *= -1.0f;
	velocity_ = direction * new_speed;
	Debug::Log(1233);
}
