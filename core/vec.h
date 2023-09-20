#pragma once
#include <cstdint>
#include <type_traits>
#include <array>
#include <cmath>

namespace engine::core {
    template<typename T, typename = typename std::enable_if<std::is_arithmetic_v<T>, T>::type>
    struct vec2 {
        T x;
        T y;

        vec2() : x(T{}), y(T{}) {}

        vec2(const T& x, const T& y) : x(x), y(y) {}

        T length() const {
            if (x == T{} && y == T{}) {
                return T{};
            }
            return static_cast<T>(std::sqrt(x * x + y * y));
        }

        T norm() const {
            T len = length();
            return {x / len}
        }
    };
}