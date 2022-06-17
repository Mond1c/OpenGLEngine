#pragma once
#include "IComponent.h"
#include "Transform.h"
#include <memory>

namespace engine {
    class Physics : public IComponent
    {
    private:
        std::shared_ptr<Transform> transform_;
    public:
        Physics(std::shared_ptr<Transform>& transform) : transform_(transform) {}
    public:
        void Update() const override;
    };
}
