#pragma once
#include "IComponent.h"
#include "Transform.h"
#include <memory>

namespace engine {
    namespace Components {
        class Physics : public IComponent
        {
        private:
            std::shared_ptr<Transform> transform_;
        public:
            Physics(std::shared_ptr<Transform>& transform) : transform_(transform) {}
            ~Physics() override = default;
        public:
            void Update() const override;
        };
    }
}
