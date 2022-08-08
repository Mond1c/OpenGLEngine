#include "Window.h"

using namespace engine;
using namespace core;

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window_);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window_);
}

void Window::SetTitle(const std::string &str) {
    glfwSetWindowTitle(window_, str.c_str());
}

bool Window::IsKeyPressed(const Key &key) const {
    return glfwGetKey(window_, static_cast<int>(key)) == GLFW_PRESS;
}

bool Window::IsKeyReleased(const Key &key) const {
    return glfwGetKey(window_, static_cast<int>(key)) == GLFW_RELEASE;
}

Vector2f engine::core::Window::GetCursorPosition() const {
    double x, y;
    glfwGetCursorPos(window_, &x, &y);
    return Vector2f(static_cast<float>(x),
                    static_cast<float>(y));
}

bool engine::core::Window::IsMouseButtonPressed(const Mouse &mouse) const {
    return glfwGetMouseButton(window_, static_cast<int>(mouse)) == GLFW_PRESS;
}

bool engine::core::Window::IsMouseButtonReleased(const Mouse &mouse) const {
    return glfwGetMouseButton(window_, static_cast<int>(mouse)) == GLFW_RELEASE;
}

