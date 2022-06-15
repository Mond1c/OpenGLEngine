#pragma once
#include "Utility.h"
#include <GLFW/glfw3.h>
#include <array>

namespace engine {
	class Object {
	protected:
		Vector2f position_;
		Vector2f size_;
		Color color_{};
	public:
		Object(Vector2f&& position, Vector2f&& size) :
			position_(position),
			size_(size) {}
		Object(Vector2f&& position, Vector2f&& size, Color&& color) :
			position_(position),
			size_(size),
			color_(color) {}
	public:
		virtual Vector2f GetPosition() const;
		virtual Vector2f GetSize() const;
		Color GetColor() const;
	public:
		virtual void SetPosition(Vector2f&& position);
		virtual void SetSize(Vector2f&& size);
		void SetColor(Color&& color);
	public:
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
		Triangle(Vector2f&& point1, Vector2f&& point2, Vector2f&& point3) :
			Object({}, {}) {
			points_[0] = std::move(point1);
			points_[1] = std::move(point2);
			points_[2] = std::move(point3);
		}
		Triangle(Vector2f&& point1, Vector2f&& point2, Vector2f&& point3, Color&& color) :
			Object({}, {}, std::move(color)) {
			points_[0] = std::move(point1);
			points_[1] = std::move(point2);
			points_[2] = std::move(point3);
		}
	public:
		std::array<Vector2f, 3> GetPoints() const;
		Vector2f GetPosition() const override;
		Vector2f GetSize() const override;
	public:
		void SetPoints(std::array<Vector2f, 3>&& points);
		void SetPosition(Vector2f&& position) override;
		void SetSize(Vector2f&& size) override;
	public:
		void Draw() const override;
	};
}
