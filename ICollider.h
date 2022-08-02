#pragma once
#include "IComponent.h"
#include "GameObject.h"
#include "Physics.h"
#include "Debug.h"
#include <iostream>
#include <memory>
#include <unordered_map>

namespace engine {
    namespace components {   
        class ICollider : public IComponent
        {
        protected:
            std::shared_ptr<Transform>& transform_;
            std::shared_ptr<Physics> physics_;
            bool isCollisionDetected_ = false;
        public:
            ICollider(std::shared_ptr<GameObject>& object) :
                transform_(object->GetTransform()), physics_(object->GetComponent<Physics>()) {}
            virtual ~ICollider() override = default;
        public:
            virtual void Update() override = 0;
        public:
            Transform GetTransform() const;
            Vector2f GetVelocity() const;
            float GetMass() const;
        public:
            void Push(engine::Vector2f otherSpeed, float otherMass);
        };

        inline std::vector<std::shared_ptr<ICollider>> ALL_COLLIDERS;

        namespace colliders {
            class Box : public ICollider {
            public:
                Box(std::shared_ptr<GameObject>& object) :
                    ICollider(object) {
                }
                ~Box() override = default;
            public:
                void Update() override;
            };

            class Circle : public ICollider {
            public:
                Circle(std::shared_ptr<GameObject>& object) :
                    ICollider(object) {}
                ~Circle() override = default;
            public:
                void Update() override;
            };

            namespace {
                inline bool detect_collision(const Box* obj1, const Box* obj2) {
                    Transform t1 = obj1->GetTransform();
                    Transform t2 = obj2->GetTransform();
                    Vector2f s1 = t1.Scale;
                    Vector2f s2 = t2.Scale;
                    Vector2f p1 = t1.Position;
                    Vector2f p2 = t2.Position;
                    return p1.x <= p2.x + s2.x &&
                        p1.x + s1.x >= p2.x &&
                        p1.y <= p2.y + s2.y &&
                        s1.y + p1.y >= p2.y;
                }

                inline bool detect_collision(const Circle* obj1, const Circle* obj2) {
                    Transform t1 = obj1->GetTransform();
                    Transform t2 = obj2->GetTransform();
                    Vector2f s1 = t1.Scale;
                    Vector2f s2 = t2.Scale;
                    Vector2f p1 = t1.Position;
                    Vector2f p2 = t2.Position;
                    float dx = (p1.x + s1.x) - (p2.x + s2.x);
                    float dy = (p1.y + s1.x) - (p2.y + s2.x);
                    return (dx * dx + dy * dy) <= (s1.x + s2.x) * (s1.x + s2.x);
                }

                inline bool detect_collision(const Box* obj1, const Circle* obj2) { // TODO: Not working
                    Vector2f cp = ToWorldPoint(obj2->GetTransform().Position);
                    Vector2f bp = ToWorldPoint(obj1->GetTransform().Position);
                    Vector2f sp = ToWorldPoint(obj1->GetTransform().Scale);
                    float tempX = cp.x, tempY = cp.y;
                    if (tempX < bp.x) tempX = bp.x;
                    else if (tempX > bp.x + sp.x) tempX = bp.x + sp.x;
                    if (cp.y < bp.y) tempY = bp.y;
                    else if (tempY > bp.y + sp.y) tempY = bp.y + sp.y;
                    float distX = cp.x - tempX;
                    float distY = cp.y - tempY;
                    float distance = distX * distX + distY * distY;
                    Vector2f scale = ToWorldPoint(obj2->GetTransform().Scale);
                    return distance <= scale.x * scale.x;
                }

                inline bool DetectCollision(const ICollider* obj1, const ICollider* obj2) {
                    if (InstanceOf<Box>(obj1) && InstanceOf<Box>(obj2))
                        return detect_collision(dynamic_cast<const Box*>(obj1), dynamic_cast<const Box*>(obj2));
                    if (InstanceOf<Circle>(obj1) && InstanceOf<Circle>(obj2))
                        return detect_collision(dynamic_cast<const Circle*>(obj1), dynamic_cast<const Circle*>(obj2));
                    if (InstanceOf<Box>(obj1) && InstanceOf<Circle>(obj2))
                        return detect_collision(dynamic_cast<const Box*>(obj1), dynamic_cast<const Circle*>(obj2));
                    if (InstanceOf<Circle>(obj1) && InstanceOf<Box>(obj2))
                        return detect_collision(dynamic_cast<const Box*>(obj2), dynamic_cast<const Circle*>(obj1));
                    return false;
                }
            }
        }
    }
}

