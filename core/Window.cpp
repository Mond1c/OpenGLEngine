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



GLFWwindow *Window::GetGLFWwindow() {
    return window_;
}

