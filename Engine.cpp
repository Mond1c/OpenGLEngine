#include "Engine.h"
#include <memory>
using namespace engine;

void Engine::Awake()
{
	window = std::make_unique<Window>(800, 800, "Hello World");
}

void Engine::Start()
{
	auto obj = CreateObject(Rectangle(Vector2f(),
		Vector2f(0.1f, 0.1f), Color(255, 255, 255)));
}

void Engine::Update()
{
}
