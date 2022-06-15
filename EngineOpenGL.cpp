#include "Window.h"
#include "Utility.h"
#include "Object.h"

#include <memory>
using namespace engine;

int main(void)
{
    if (!glfwInit())
        return -1;
    Window window(640, 480, "Hello World");
    std::unique_ptr<Object> obj = std::make_unique<Triangle>(Vector2f(-0.5f, -0.5f), Vector2f(0, 0.5f),
        Vector2f(0.5f, -0.5f), Color(255, 0, 0));


    /* Loop until the user closes the window */
    while (!window.ShouldClose())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        obj->Draw();

        /* Swap front and back buffers */
        window.SwapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}