#pragma once

#include "Utility.h"
#include <iostream>

namespace engine {
    class Debug {
    public:
        template<typename T>
        static void Log(const T &obj) {
            std::cout << obj << std::endl;
        }

        template<typename T>
        static void Log(const core::Vector2 <T> &vector) {
            std::cout << "{" << vector.x << ", " << vector.y << "}" << std::endl;
        }

        static void Log(const core::Color &color) {
            std::cout << "(" << color.r << ", " << color.g << ", " << color.b
                      << ", " << color.a << ")" << std::endl;
        }
    };
}

