#pragma once

#include <GLFW/glfw3.h>
#include <exception>
#include <string>
#include "Utility.h"

namespace engine::core {
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

    class Window {
    private:
        GLFWwindow *window_;
    public:
        Window(int width, int height, const char *title) {
            window_ = glfwCreateWindow(width, height, title, NULL, NULL);
            if (!window_) {
                glfwTerminate();
                throw std::exception("Can't create a window");
            }
            glfwMakeContextCurrent(window_);
            glViewport(0.0f, 0.0f, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
        }

    public:
        Window(Window &) = delete;

        Window(Window &&) = delete;

    public:
        Window &operator=(Window &) = delete;

        Window &operator=(Window &&) = delete;

    public:
        [[nodiscard]] bool ShouldClose() const;

        void SwapBuffers();

        void SetTitle(const std::string &str);

        [[nodiscard]] bool IsKeyPressed(const Key &key) const;

        [[nodiscard]] bool IsKeyReleased(const Key &key) const;

        [[nodiscard]] Vector2f GetCursorPosition() const;

        [[nodiscard]] bool IsMouseButtonPressed(const Mouse &mouse) const;

        [[nodiscard]] bool IsMouseButtonReleased(const Mouse &mouse) const;
    };
}

