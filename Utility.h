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
	};

	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;

	struct Color {
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;

		Color() : 
			r(0), g(0), b(0), a(255) {}

		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
			r(r), g(g), b(b), a(a) {}
	};

	template<typename T>
	Vector2<T> ToScreenPoint(const Vector2<T>& point) {
		return { point.x / WIDTH, point.y / HEIGHT };
	}

	template<typename T>
	Vector2<T> ToWorldPoint(const Vector2<T>& point) {
		return { point.x * WIDTH, point.y * HEIGHT };
	}
}