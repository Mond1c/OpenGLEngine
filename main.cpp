#include "Engine.h"
using namespace engine;

int main() {
    if (!glfwInit())
        return -1;
    Engine* engine = Engine::GetInstance();
    engine->Awake();
    engine->Start();
    engine->Loop();
    delete engine;
    return 0;
}