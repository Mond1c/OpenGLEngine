#include "Engine.h"
#include "Physics.h"
#include <memory>
using namespace engine;

void Engine::Awake()
{
	CreateWindow(800, 800, "Simple Engine");
}

void Engine::Start()
{
	auto circle = CreateObject(Circle(Vector2f(), 100, Color(255, 255, 255)));
	circle->AddComponent(std::make_shared<Physics>(circle->GetTransform()));
}

void Engine::Update()
{
}
