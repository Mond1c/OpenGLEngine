#pragma once
#include "IComponent.h"
#include "Transform.h"
#include <memory>

namespace engine {
    namespace components {
        class Physics : public IComponent
        {
        private:
            std::shared_ptr<Transform> transform_;
            Vector2f velocity_{};
            float mass_;
            bool isGravityEnabled_ = true;
        public:
            Physics(std::shared_ptr<Transform>& transform, float mass) : transform_(transform), mass_(mass) {}
            ~Physics() override = default;
        public:
            void Update() override;
        public:
            float GetMass() const;
            Vector2f GetVelocity() const;
        public:
            void SetVelocity(const Vector2f& velocity);
            void EnableGravity();
            void DisableGravity();
        public:
            void Push(const Vector2f& otherSpeed, float otherMass);
        };
    }
}
