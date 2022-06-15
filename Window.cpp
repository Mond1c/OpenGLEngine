#include "Window.h"

bool engine::Window::ShouldClose()
{
    return glfwWindowShouldClose(window);
}

void engine::Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}
