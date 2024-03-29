#pragma once

#include "Settings.h"
#include <numeric>
#include <string>
#include <cmath>
#include <cstdint>

namespace engine::core {
    template<typename Child, typename Base>
    inline bool InstanceOf(const Base *base) {
        return dynamic_cast<const Child *>(base) != nullptr;
    }

    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    struct Vector2 {
        T x;
        T y;

        Vector2() : x(0), y(0) {}

        Vector2(T x, T y) : x(x), y(y) {}

        [[nodiscard]] T Magnitude() const {
            if (x == 0.0f && y == 0.0f) return 0.0f;
            return static_cast<T>(std::sqrt(x * x + y * y));
        }

        [[nodiscard]] Vector2 Normalize() const {
            T length = Magnitude();
            return {x / length, y / length};
        }

        static const Vector2<T> Zero;

        Vector2 operator+=(const Vector2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        Vector2 operator-=(const Vector2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        Vector2 operator*=(const T& value) {
            x *= value;
            y *= value;
            return *this;
        }

        friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
            return Vector2(lhs) += rhs;
        }

        friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
            return Vector2(lhs) -= rhs;
        }

        friend Vector2 operator*(const Vector2& lhs, const T& rhs) {
            return Vector2(lhs) *= rhs;
        }

        friend Vector2 operator*(const T& lhs, const Vector2& rhs) {
            return rhs * lhs;
        }

        friend bool operator==(const Vector2& lhs, const Vector2& rhs) {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        friend bool operator!=(const Vector2& lhs, const Vector2& rhs) {
            return !(lhs == rhs);
        }
    };

    typedef Vector2<int> Vector2i;
    typedef Vector2<float> Vector2f;

    template<> inline const Vector2i Vector2i::Zero = Vector2i(0, 0);
    template<> inline const Vector2f Vector2f::Zero = Vector2f(0, 0);

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

        static Color Parse(const std::string& r, const std::string& g, const std::string& b, const std::string& a) {
            return {static_cast<uint8_t>(std::stoi(r)), static_cast<uint8_t>(std::stoi(g)),
                    static_cast<uint8_t>(std::stoi(b)), static_cast<uint8_t>(std::stoi(a))};
        }

        friend std::string to_string(const Color& color) {
            return std::to_string(color.r) + "," + std::to_string(color.g) + ","
                    + std::to_string(color.b) + "," + std::to_string(color.a);
        }
    };

    inline const Color Color::White = Color(255, 255, 255);
    inline const Color Color::Black = Color(0, 0, 0);
    inline const Color Color::Red = Color(255, 0, 0);
    inline const Color Color::Green = Color(0, 255, 0);
    inline const Color Color::Blue = Color(0, 0, 255);

    inline Vector2f ParseVector2f(const std::string &x, const std::string &y) {
        return {std::stof(x), std::stof(y)};
    }

    template<typename T>
    inline Vector2<T> ToScreenPoint(const Vector2<T> &point) {
        return {point.x / WIDTH, point.y / HEIGHT};
    }

    template<typename T>
    inline Vector2<T> ToWorldPoint(const Vector2<T> &point) {
        return {point.x * WIDTH, point.y * HEIGHT};
    }

    inline std::string Vector2fToString(const Vector2f &vec) {
        Vector2f v = ToWorldPoint(vec);
        return std::to_string(v.x) + "," + std::to_string(v.y);
    }
}
