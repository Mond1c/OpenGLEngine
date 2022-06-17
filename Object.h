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
		Object(Vector2f&& position, Vector2f&& scale) :
			transform_(std::make_shared<Transform>(std::move(position), std::move(scale))) {}
		Object(Vector2f&& position, Vector2f&& scale, Color&& color) :
			transform_(std::make_shared<Transform>(std::move(position), std::move(scale))),
			color_(color) {}
	public:
		virtual Vector2f GetPosition() const;
		virtual Vector2f GetSize() const;
		Color GetColor() const;
		std::shared_ptr<Transform>& GetTransform();
	public:
		virtual void SetPosition(Vector2f&& position);
		virtual void SetScale(Vector2f&& size);
		void SetColor(Color&& color);
	public:
		void AddComponent(std::shared_ptr<IComponent> component);
		void Update();
		virtual void Draw() const = 0;
	};

	class Rectangle : public Object {
	public:
		Rectangle(Vector2f&& position, Vector2f&& size) :
			Object(std::move(position), std::move(size)) {}
		Rectangle(Vector2f&& position, Vector2f&& size, Color&& color) :
			Object(std::move(position), std::move(size), std::move(color)) {}
	public:
		void Draw() const override;
	};

	class Triangle : public Object {
	private:
		std::array<Vector2f, 3> points_;
	public:
		Triangle(Vector2f&& position, Vector2f scale, Vector2f&& point1, Vector2f&& point2, Vector2f&& point3) :
			Object(std::move(position), std::move(scale)) {
			points_[0] = ToScreenPoint(std::move(point1));
			points_[1] = ToScreenPoint(std::move(point2));
			points_[2] = ToScreenPoint(std::move(point3));
		}
		Triangle(Vector2f&& position, Vector2f scale, Vector2f&& point1, Vector2f&& point2, Vector2f&& point3, Color&& color) :
			Object(std::move(position), std::move(scale), std::move(color)) {
			points_[0] = ToScreenPoint(std::move(point1));
			points_[1] = ToScreenPoint(std::move(point2));
			points_[2] = ToScreenPoint(std::move(point3));
		}
	public:
		std::array<Vector2f, 3> GetPoints() const;
	public:
		void SetPoints(std::array<Vector2f, 3>&& points);
	public:
		void Draw() const override;
	};

	class Point : public Object {
	public:
		Point(Vector2f&& position) :
			Object(std::move(position), {}) {}
		Point(Vector2f&& position, Color&& color) :
			Object(std::move(position), {}, std::move(color)) {}
	public:
		void SetScale(Vector2f&& size) override;
	public:
		void Draw() const override;
	};

	class Line : public Object {
	private:
		Vector2f point_;
	public:
		Line(Vector2f&& position, Vector2f&& point) :
			Object(std::move(position), {}), point_(ToScreenPoint(std::move(point))) {}
		Line(Vector2f&& position, Vector2f&& point, Color&& color) :
			Object(std::move(position), {}, std::move(color)), point_(ToScreenPoint(std::move(point))) {}
	public:
		void SetScale(Vector2f&& size) override;
	public:
		void Draw() const override;
	};

	class Polygon : public Object {
	private:
		std::vector<Vector2f> vertixes_;
	private:
		void UpdateVertixes();
	public:
		Polygon(Vector2f&& position, Vector2f scale, std::vector<Vector2f>&& vertixes) :
			Object(std::move(position), std::move(scale)), vertixes_(std::move(vertixes)) {
			UpdateVertixes();
		}
		Polygon(Vector2f&& position, Vector2f scale, std::vector<Vector2f>&& vertixes, Color&& color) :
			Object(std::move(position), std::move(scale), std::move(color)), vertixes_(std::move(vertixes)) {
			UpdateVertixes();
		}
	public:
		void Draw() const override;
	};

	class Circle : public Object {
	public:
		Circle(Vector2f&& position, float radius) :
			Object(std::move(position), std::move(ToScreenPoint<float>({ radius, radius }))) {}
		Circle(Vector2f&& position, float radius, Color&& color) :
			Object(std::move(position), std::move(ToScreenPoint<float>({ radius, radius })), std::move(color)) {}
	public:
		void Draw() const override;
	};
}
