#pragma once

#include "IComponent.h"
#include "Window.h"

namespace engine::core {
    class MonoBehaviour : public IComponent {
    protected:
        std::shared_ptr<Transform> transform;
        std::shared_ptr<Window> &window;
    public:
        MonoBehaviour(std::shared_ptr<GameObject> &obj, std::shared_ptr<Window> &window)
                : transform(obj->GetTransform()), window(window) {
        }

        ~MonoBehaviour() override = default;

    public:
        virtual void Start() = 0;

        void Update() override = 0;
    };
}
