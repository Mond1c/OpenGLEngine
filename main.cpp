#include "Engine.h"

#include <memory>
using namespace engine;

int main(void)
{
    if (!glfwInit())
        return -1;
    Engine engine;
    engine.Awake();
    engine.Start();
    engine.Loop();
    return 0;
}