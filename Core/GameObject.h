#pragma once

#include "IComponent.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include <array>
#include <utility>
#include <vector>
#include <memory>
#include <sstream>

namespace engine::core {
    class GameObject {
    protected:
        std::shared_ptr<Transform> transform_;
        std::vector<std::shared_ptr<IComponent>> components_;
        Color color_{};
    public:
        GameObject(const Vector2f &position, const Vector2f &scale) :
                transform_(std::make_shared<Transform>(position, scale)) {}

        GameObject(const Vector2f &position, const Vector2f &scale, const Color &color) :
                transform_(std::make_shared<Transform>(position, scale)),
                color_(color) {}

        virtual ~GameObject() = default;

    public:
        [[nodiscard]] virtual Vector2f GetPosition() const;

        [[nodiscard]] virtual Vector2f GetSize() const;

        [[nodiscard]] Color GetColor() const;

        std::shared_ptr<Transform> &GetTransform();

    public:
        template<typename T, typename = typename std::enable_if<std::is_base_of<IComponent, T>::value>::type>
        std::shared_ptr<T> GetComponent() {
            for (auto &component : components_) {
                if (InstanceOf<T>(component.get())) return std::static_pointer_cast<T>(component);
            }
            return nullptr;
        }

        void StartAllMonoBehaviourComponents();

    public:
        virtual void SetPosition(const Vector2f &position);

        virtual void SetScale(const Vector2f &size);

        void SetColor(const Color &color);

    public:
        void AddComponent(const std::shared_ptr<IComponent> &component);

        void Update();

    public:
        virtual void Draw() const = 0;

        virtual void StringToObject(std::stringstream &ss) = 0;

        [[nodiscard]] virtual std::string GetString() const = 0;
    };

    class Rectangle : public GameObject {
    public:
        Rectangle(const Vector2f &position, const Vector2f &size) :
                GameObject(position, size) {}

        Rectangle(const Vector2f &position, const Vector2f &size, const Color &color) :
                GameObject(position, size, color) {}

        ~Rectangle() override = default;

    public:
        void Draw() const override;

        void StringToObject(std::stringstream &ss) override;

        [[nodiscard]] std::string GetString() const override;
    };

    class Triangle : public GameObject {
    private:
        std::array<Vector2f, 3> points_;
    public:
        Triangle(const Vector2f &position, const Vector2f &scale, const Vector2f &point1, const Vector2f &point2,
                 const Vector2f &point3) :
                GameObject(position, scale) {
            points_[0] = ToScreenPoint(point1);
            points_[1] = ToScreenPoint(point2);
            points_[2] = ToScreenPoint(point3);
        }

        Triangle(const Vector2f &position, const Vector2f &scale, const Vector2f &point1, const Vector2f &point2,
                 const Vector2f &point3, const Color &color) :
                GameObject(position, scale, color) {
            points_[0] = ToScreenPoint(point1);
            points_[1] = ToScreenPoint(point2);
            points_[2] = ToScreenPoint(point3);
        }

        ~Triangle() override = default;

    public:
        [[nodiscard]] std::array<Vector2f, 3> GetPoints() const;

    public:
        void SetPoints(const std::array<Vector2f, 3> &points);

    public:
        void Draw() const override;

        void StringToObject(std::stringstream &ss) override;

        [[nodiscard]] std::string GetString() const override;
    };

    class Point : public GameObject {
    public:
        explicit Point(const Vector2f &position) :
                GameObject(position, {}) {}

        Point(const Vector2f &position, const Color &color) :
                GameObject(position, {}, color) {}

        ~Point() override = default;

    public:
        void SetScale(const Vector2f &size) override;

    public:
        void Draw() const override;

        void StringToObject(std::stringstream &ss) override;

        [[nodiscard]] std::string GetString() const override;
    };

    class Line : public GameObject {
    private:
        Vector2f point_;
    public:
        Line(const Vector2f &position, const Vector2f &point) :
                GameObject(position, {}), point_(ToScreenPoint(point)) {}

        Line(const Vector2f &position, const Vector2f &point, const Color &color) :
                GameObject(position, {}, color), point_(ToScreenPoint(point)) {}

        ~Line() override = default;

    public:
        void SetScale(const Vector2f &size) override;

    public:
        void Draw() const override;

        void StringToObject(std::stringstream &ss) override;

        [[nodiscard]] std::string GetString() const override;
    };

    class Polygon : public GameObject {
    private:
        std::vector<Vector2f> vertices_;
    private:
        [[nodiscard]] std::vector<Vector2f> GetVertices() const;

    public:
        Polygon(const Vector2f &position, const Vector2f &scale, std::vector<Vector2f> vertices) :
                GameObject(position, scale), vertices_(std::move(vertices)) {}

        Polygon(const Vector2f &position, const Vector2f &scale, std::vector<Vector2f> vertices,
                const Color &color) :
                GameObject(position, scale, color), vertices_(std::move(vertices)) {}

        ~Polygon() override = default;

    public:
        void Draw() const override;

        void StringToObject(std::stringstream &ss) override;

        [[nodiscard]] std::string GetString() const override;
    };

    class Circle : public GameObject {
    public:
        Circle(const Vector2f &position, float radius) :
                GameObject(position, ToScreenPoint<float>({radius, radius})) {}

        Circle(const Vector2f &position, float radius, const Color &color) :
                GameObject(position, ToScreenPoint<float>({radius, radius}), color) {}

        ~Circle() override = default;

    public:
        void Draw() const override;

        void StringToObject(std::stringstream &ss) override;

        [[nodiscard]] std::string GetString() const override;
    };
}
