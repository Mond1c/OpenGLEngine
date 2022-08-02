#pragma once
#include "Settings.h"
#include <numeric>
#include <string>
#include <cmath>

namespace engine::core {
	template< typename Child, typename Base>
	inline bool InstanceOf(const Base* base) {
		return dynamic_cast<const Child*>(base) != nullptr;
	}

	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	struct Vector2 {
		T x;
		T y;
		Vector2() : x(0), y(0) {}
		Vector2(T x, T y) : x(x), y(y) {}

		T Magnitude() const {
			if (x == 0.0f && y == 0.0f) return 0.0f;
			return static_cast<T>(std::sqrt(x * x + y * y));
		}

		Vector2 Normolize() const {
			T length = Magnitude();
			return { x / length, y / length };
		}

		static const Vector2<T> Zero;
	};

	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;

	inline const Vector2i Vector2i::Zero = Vector2i(0, 0);
	inline const Vector2f Vector2f::Zero = Vector2f(0, 0);

	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color() : 
			r(0), g(0), b(0), a(255) {}

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
			r(r), g(g), b(b), a(a) {}

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
	};

	inline const Color Color::White = Color(255, 255, 255);
	inline const Color Color::Black = Color(0, 0, 0);
	inline const Color Color::Red = Color(255, 0, 0);
	inline const Color Color::Green = Color(0, 255, 0);
	inline const Color Color::Blue = Color(0, 0, 255);

	inline Color ParseColor(const std::string& r, const std::string& g, const std::string& b, const std::string& a) {
		return Color(std::stoi(r), std::stoi(g), std::stoi(b), std::stoi(a));
	}

	inline std::string ColorToString(const Color& color) {
		return std::to_string(color.r) + "," + std::to_string(color.g) + "," 
			+ std::to_string(color.b) + "," + std::to_string(color.a);
	}

	inline Vector2f ParseVector2f(const std::string& x, const std::string& y) {
		return Vector2f(std::stof(x), std::stof(y));
	}

	template<typename T>
	inline Vector2<T> ToScreenPoint(const Vector2<T>& point) {
		return { point.x / WIDTH, point.y / HEIGHT };
	}

	template<typename T>
	inline Vector2<T> ToWorldPoint(const Vector2<T>& point) {
		return { point.x * WIDTH, point.y * HEIGHT };
	}

	inline std::string Vector2fToString(const Vector2f& vec) {
		Vector2f v = ToWorldPoint(vec);
		return std::to_string(v.x) + "," + std::to_string(v.y);
	}

	template<typename T>
	inline Vector2<T> operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template<typename T>
	inline Vector2<T> operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x - rhs.x, lhs.y * rhs.y);
	}

	template<typename T>
	inline Vector2<T> operator*(const Vector2<T>& lhs, T rhs) {
		return Vector2<T>(lhs.x * rhs, lhs.y * rhs);
	}

	template<typename T>
	inline Vector2<T>& operator+=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x += rhs.x; lhs.y += rhs.y;
		return lhs;
	}

	template<typename T>
	inline Vector2<T>& operator-=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x -= rhs.x; lhs.y -= rhs.y;
		return lhs;
	}

	template<typename T>
	inline Vector2<T>& operator*=(Vector2<T>& lhs, T rhs) {
		lhs.x *= rhs; lhs.y *= rhs;
		return lhs;
	}
}