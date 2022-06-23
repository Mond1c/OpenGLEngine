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

        //std::unordered_map<ICollider*, std::shared_ptr<ICollider>> ALL_COLLISIONS;
        inline std::vector<std::shared_ptr<ICollider>> ALL_COLLIDERS;

        namespace Colliders {
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
                template< typename Child, typename Base>
                inline bool InstanceOf(const Base* base) {
                    return dynamic_cast<const Child*>(base) != nullptr;
                }


                inline bool detect_collision(const Box* obj1, const Box* obj2) {
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

                inline bool DetectCollision(const ICollider* obj1, const ICollider* obj2) {
                    if (InstanceOf<Box>(obj1) && InstanceOf<Box>(obj2))
                        return detect_collision(dynamic_cast<const Box*>(obj1), dynamic_cast<const Box*>(obj2));
                    return false;
                }
            }
        }
    }
}

