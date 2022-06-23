#pragma once
#include "IComponent.h"
#include "Object.h"
#include <iostream>
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
                    ICollider(transform) {  
                }
                ~Box() override = default;
            public:
                void Update() const override;
            };

            namespace {
                inline bool DetectCollision(const ICollider const* obj1, const ICollider const* obj2) {
                    return DetectCollision(obj1, obj2);
                }

                inline bool DetectCollision(const Box const* obj1, const Box const* obj2) {
                    std::shared_ptr<Transform> t1 = obj1->transform_;
                    std::shared_ptr<Transform> t2 = obj2->transform_;
                    Vector2f s1 = ToWorldPoint(t1->Scale);
                    Vector2f s2 = ToWorldPoint(t2->Scale);
                    Vector2f p1 = ToWorldPoint(t1->Position);
                    Vector2f p2 = ToWorldPoint(t2->Position);
                    return p1.x < p2.x + s2.x &&
                        p1.x + s1.x > p2.x &&
                        p1.y < p2.y + s2.y &&
                        s1.y + p1.y > p2.y;
                }
            }
        }
    }
}

