#include "Engine.h"
using namespace engine;

int main(void)
{
    if (!glfwInit())
        return -1;
    Engine::Awake();
    Engine::Start();
    Engine::Loop();
    return 0;
}