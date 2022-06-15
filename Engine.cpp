#include "Engine.h"
#include <memory>
using namespace engine;

void Engine::Awake()
{
	CreateWindow(800, 800, "Simple Engine");
}

void Engine::Start()
{
	auto circle = CreateObject(Circle(Vector2f(), 800.0f, Color(255, 255, 255)));
}

void Engine::Update()
{
}
