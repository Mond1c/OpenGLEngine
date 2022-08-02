#pragma once
#include "IComponent.h"
#include "Transform.h"
#include <memory>

namespace engine::components {
        class Physics : public core::IComponent
        {
        private:
            std::shared_ptr<core::Transform> transform_;
            core::Vector2f velocity_{};
            float mass_;
            bool isGravityEnabled_ = true;
        public:
            Physics(std::shared_ptr<core::Transform>& transform, float mass) : transform_(transform), mass_(mass) {}
            ~Physics() override = default;
        public:
            void Update() override;
        public:
            float GetMass() const;
            core::Vector2f GetVelocity() const;
        public:
            void SetVelocity(const core::Vector2f& velocity);
            void EnableGravity();
            void DisableGravity();
        public:
            void Push(const core::Vector2f& otherSpeed, float otherMass);
        };
}
