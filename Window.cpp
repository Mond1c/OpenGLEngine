#include "Window.h"
using namespace engine;
using namespace core;

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(window_);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window_);
}

void Window::SetTitle(const std::string& str)
{
    glfwSetWindowTitle(window_, str.c_str());
}

bool Window::IsKeyPressed(const Key& key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

bool Window::IsKeyReleased(const Key& key)
{
    return glfwGetKey(window_, key) == GLFW_RELEASE;
}

