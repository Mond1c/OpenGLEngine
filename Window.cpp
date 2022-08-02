#include "Window.h"

bool engine::Window::ShouldClose()
{
    return glfwWindowShouldClose(window_);
}

void engine::Window::SwapBuffers()
{
    glfwSwapBuffers(window_);
}

void engine::Window::SetTitle(const std::string& str)
{
    glfwSetWindowTitle(window_, str.c_str());
}

bool engine::Window::IsKeyPressed(const engine::Key& key)
{
    return glfwGetKey(window_, key) == GLFW_PRESS;
}

bool engine::Window::IsKeyReleased(const Key& key)
{
    return glfwGetKey(window_, key) == GLFW_RELEASE;
}

