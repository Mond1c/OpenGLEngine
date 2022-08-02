#include "Window.h"

bool engine::Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void engine::Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void engine::Window::SetTitle(const std::string& str)
{
    glfwSetWindowTitle(window, str.c_str());
}
