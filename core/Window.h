#pragma once

#include <GLFW/glfw3.h>
#include <exception>
#include <string>
#include "Utility.h"

namespace engine::core {
    class Window {
    private:
        GLFWwindow *window_;
    public:
        Window(int width, int height, const char *title) {
            window_ = glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (!window_) {
                glfwTerminate();
                throw std::exception();
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

        GLFWwindow* GetGLFWwindow();


    };
}
