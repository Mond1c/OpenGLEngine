//
// Created by pocht on 19.08.2022.
//

#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H
#include "Window.h"

namespace engine::core {
    class Input {
    public:
        enum class Key {
            Escape = GLFW_KEY_ESCAPE,
            F1 = GLFW_KEY_F1,
            F2 = GLFW_KEY_F2,
            F3 = GLFW_KEY_F3,
            F4 = GLFW_KEY_F4,
            F5 = GLFW_KEY_F5,
            F6 = GLFW_KEY_F6,
            F7 = GLFW_KEY_F7,
            F8 = GLFW_KEY_F8,
            F9 = GLFW_KEY_F9,
            F10 = GLFW_KEY_F10,
            F11 = GLFW_KEY_F11,
            F12 = GLFW_KEY_F12,
            PrintScreen = GLFW_KEY_PRINT_SCREEN,
            ScrollLock = GLFW_KEY_SCROLL_LOCK,
            Pause = GLFW_KEY_PAUSE,
            One = GLFW_KEY_1,
            Two = GLFW_KEY_2,
            Three = GLFW_KEY_3,
            Four = GLFW_KEY_4,
            Five = GLFW_KEY_5,
            Six = GLFW_KEY_6,
            Seven = GLFW_KEY_7,
            Eight = GLFW_KEY_8,
            Nine = GLFW_KEY_9,
            Zero = GLFW_KEY_0,
            Minus = GLFW_KEY_MINUS,
            Equal = GLFW_KEY_EQUAL,
            BackSpace = GLFW_KEY_BACKSPACE,
            Insert = GLFW_KEY_INSERT,
            Home = GLFW_KEY_HOME,
            PageUp = GLFW_KEY_PAGE_UP,
            PageDown = GLFW_KEY_PAGE_DOWN,
            Delete = GLFW_KEY_DELETE,
            End = GLFW_KEY_END,
            Tab = GLFW_KEY_TAB,
            CapsLock = GLFW_KEY_CAPS_LOCK,
            LeftShift = GLFW_KEY_LEFT_SHIFT,
            LeftControl = GLFW_KEY_LEFT_CONTROL,
            LeftAlt = GLFW_KEY_LEFT_ALT,
            Space = GLFW_KEY_SPACE,
            RightAlt = GLFW_KEY_RIGHT_ALT,
            RightControl = GLFW_KEY_RIGHT_CONTROL,
            RightShift = GLFW_KEY_RIGHT_SHIFT,
            Enter = GLFW_KEY_ENTER,
            Up = GLFW_KEY_UP,
            Down = GLFW_KEY_DOWN,
            Left = GLFW_KEY_LEFT,
            Right = GLFW_KEY_RIGHT,
            Q = GLFW_KEY_Q,
            W = GLFW_KEY_W,
            E = GLFW_KEY_Q,
            R = GLFW_KEY_Q,
            T = GLFW_KEY_Q,
            Y = GLFW_KEY_Q,
            U = GLFW_KEY_Q,
            I = GLFW_KEY_Q,
            O = GLFW_KEY_Q,
            P = GLFW_KEY_Q,
            LeftBracket = GLFW_KEY_LEFT_BRACKET,
            RightBracket = GLFW_KEY_RIGHT_BRACKET,
            Backslash = GLFW_KEY_BACKSLASH,
            A = GLFW_KEY_A,
            S = GLFW_KEY_S,
            D = GLFW_KEY_D,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            Semicolon = GLFW_KEY_SEMICOLON,
            Apostrophe = GLFW_KEY_APOSTROPHE,
            Z = GLFW_KEY_Z,
            X = GLFW_KEY_X,
            C = GLFW_KEY_C,
            V = GLFW_KEY_V,
            B = GLFW_KEY_B,
            N = GLFW_KEY_N,
            M = GLFW_KEY_M,
            Comma = GLFW_KEY_COMMA,
            Period = GLFW_KEY_PERIOD,
            Slash = GLFW_KEY_SLASH,
        };

        enum class Mouse {
            Left = GLFW_MOUSE_BUTTON_LEFT,
            Right = GLFW_MOUSE_BUTTON_RIGHT,
            Middle = GLFW_MOUSE_BUTTON_MIDDLE
        };
    private:
        GLFWwindow* window_;
    public:
        explicit Input(Window* window) : window_(window->GetGLFWwindow()) {}
        explicit Input(std::shared_ptr<Window>& window) : window_(window->GetGLFWwindow()) {}
    public:
        [[nodiscard]] bool IsKeyPressed(const Key &key) const {
            return glfwGetKey(window_, static_cast<int>(key)) == GLFW_PRESS;
        }

        [[nodiscard]] bool IsKeyReleased(const Key &key) const {
            return glfwGetKey(window_, static_cast<int>(key)) == GLFW_RELEASE;
        }

        [[nodiscard]] Vector2f GetCursorPosition() const {
            double x, y;
            glfwGetCursorPos(window_, &x, &y);
            return Vector2f(static_cast<float>(x),
                            static_cast<float>(y));
        }

        [[nodiscard]] bool IsMouseButtonPressed(const Mouse &mouse) const {
            return glfwGetMouseButton(window_, static_cast<int>(mouse)) == GLFW_PRESS;
        }

        [[nodiscard]] bool IsMouseButtonReleased(const Mouse &mouse) const {
            return glfwGetMouseButton(window_, static_cast<int>(mouse)) == GLFW_RELEASE;
        }
    };
}

#endif //ENGINE_INPUT_H
