#pragma once
#include "IComponent.h"
#include "Transform.h"
#include <GLFW/glfw3.h>
#include <array>
#include <vector>
#include <memory>

namespace engine {
	class Object {
	protected:
		std::shared_ptr<Transform> transform_;
		std::vector<std::shared_ptr<IComponent>> components_;
		Color color_{};
	public:
		Object(const Vector2f& position, const Vector2f& scale) :
			transform_(std::make_shared<Transform>(position, scale)) {}
		Object(const Vector2f& position, const Vector2f& scale, const Color& color) :
			transform_(std::make_shared<Transform>(position, scale)),
			color_(color) {}
	public:
		virtual Vector2f GetPosition() const;
		virtual Vector2f GetSize() const;
		Color GetColor() const;
		std::shared_ptr<Transform>& GetTransform();
	public:
		virtual void SetPosition(const Vector2f& position);
		virtual void SetScale(const Vector2f& size);
		void SetColor(const Color& color);
	public:
		void AddComponent(std::shared_ptr<IComponent> component);
		void Update();
		virtual void Draw() const = 0;
	};
	
	class Rectangle : public Object {
	public:
		Rectangle(const Vector2f& position, const Vector2f& size) :
			Object(position, size) {}
		Rectangle(const Vector2f& position, const Vector2f& size, const Color& color) :
			Object(position, size, color) {}
	public:
		void Draw() const override;
	};

	class Triangle : public Object {
	private:
		std::array<Vector2f, 3> points_;
	public:
		Triangle(const Vector2f& position, const Vector2f& scale, const Vector2f& point1, const Vector2f& point2,
		 const Vector2f& point3) :
			Object(position, scale) {
				points_[0] = ToScreenPoint(point1);
				points_[1] = ToScreenPoint(point2);
				points_[2] = ToScreenPoint(point3);
		}
		Triangle(const Vector2f& position, const Vector2f& scale, const Vector2f& point1, const Vector2f& point2,
			const Vector2f& point3, const Color& color) :
				Object(position, scale, color) {
				points_[0] = ToScreenPoint(point1);
				points_[1] = ToScreenPoint(point2);
				points_[2] = ToScreenPoint(point3);
		}
	public:
		std::array<Vector2f, 3> GetPoints() const;
	public:
		void SetPoints(const std::array<Vector2f, 3>& points);
	public:
		void Draw() const override;
	};

	class Point : public Object {
	public:
		Point(const Vector2f& position) :
			Object(position, {}) {}
		Point(const Vector2f& position, const Color& color) :
			Object(position, {}, color) {}
	public:
		void SetScale(const Vector2f& size) override;
	public:
		void Draw() const override;
	};

	class Line : public Object {
	private:
		Vector2f point_;
	public:
		Line(const Vector2f& position, const Vector2f& point) :
			Object(position, {}), point_(ToScreenPoint(point)) {}
		Line(const Vector2f& position, const Vector2f& point, const Color& color) :
			Object(position, {}, color), point_(ToScreenPoint(point)) {}
	public:
		void SetScale(const Vector2f& size) override;
	public:
		void Draw() const override;
	};

	class Polygon : public Object {
	private:
		std::vector<Vector2f> vertices_;
	private:
		void UpdateVertices();
	public:
		Polygon(const Vector2f& position, const Vector2f& scale, const std::vector<Vector2f>& vertices) :
			Object(position, scale), vertices_(vertices) {
			UpdateVertices();
		}
		Polygon(const Vector2f& position, const Vector2f& scale, const std::vector<Vector2f>& vertices, const Color& color) :
			Object(position, scale, color), vertices_(vertices_) {
			UpdateVertices();
		}
	public:
		void Draw() const override;
	};

	class Circle : public Object {
	public:
		Circle(const Vector2f& position, float radius) :
			Object(position, ToScreenPoint<float>({ radius, radius })) {}
		Circle(const Vector2f& position, float radius, const Color& color) :
			Object(position, ToScreenPoint<float>({ radius, radius }), color) {}
	public:
		void Draw() const override;
	};
}
