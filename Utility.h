#pragma once
#include "Settings.h"

#include <numeric>
#include <cmath>

namespace engine {
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	struct Vector2 {
		T x;
		T y;
		Vector2() : x(0), y(0) {}
		Vector2(T x, T y) : x(x), y(y) {}

		T Magnitude() {
			return static_cast<T>(std::sqrt(x * x + y * y));
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

	template<typename T>
	inline Vector2<T> ToScreenPoint(const Vector2<T>& point) {
		return { point.x / WIDTH, point.y / HEIGHT };
	}

	template<typename T>
	inline Vector2<T> ToWorldPoint(const Vector2<T>& point) {
		return { point.x * WIDTH, point.y * HEIGHT };
	}

	template<typename T>
	inline Vector2<T>& operator+(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template<typename T>
	inline Vector2<T>& operator-(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(lhs.x - rhs.x, lhs.y * rhs.y);
	}

	template<typename T>
	inline Vector2<T>& operator*(const Vector2<T>& lhs, T rhs) {
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
	inline Vector2<T>& operator*=(Vector2<T>& lhs, const Vector2<T>& rhs) {
		lhs.x *= rhs; lhs.y *= rhs;
		return lhs;
	}
}