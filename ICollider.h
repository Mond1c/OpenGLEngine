#pragma once
#include "IComponent.h"
#include "Object.h"
#include <memory>
#include <unordered_map>

namespace engine {
    namespace Components {        
        class ICollider : public IComponent
        {
        public:
            std::shared_ptr<Transform>& transform_;
        public:
            ICollider(std::shared_ptr<Transform>& transform) :
                transform_(transform) {}
            virtual ~ICollider() override = default;
        public:
            virtual void Update() const override = 0;
        };


        namespace Colliders {
            namespace {
                static std::unordered_map<std::shared_ptr<ICollider>, std::shared_ptr<ICollider>> Collisions;
                static std::vector<std::shared_ptr<ICollider>> Colliders;
            }
            class Box : public ICollider {
            public:
                Box(std::shared_ptr<Transform>& transform) :
                    ICollider(transform) {}
                ~Box() override = default;
            public:
                void Update() const override;
            };

            namespace {
                inline bool DetectCollision(std::shared_ptr<Object>& obj1, std::shared_ptr<Object>& obj2) {
                    return DetectCollision(obj1, obj2);
                }

                inline bool DetectCollision(std::shared_ptr<Box>& obj1, std::shared_ptr<Box>& obj2) {
                    std::shared_ptr<Transform> t1 = obj1->transform_;
                    std::shared_ptr<Transform> t2 = obj2->transform_;
                    Vector2f scale1 = ToWorldPoint(t1->Scale);
                    Vector2f scale2 = ToWorldPoint(t2->Scale);
                    return t1->Position.x < t2->Position.x + scale2.x &&
                        t1->Position.x + scale1.x > t2->Position.x;
                }
            }
        }
    }
}

