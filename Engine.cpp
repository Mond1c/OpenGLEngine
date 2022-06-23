#include "Engine.h"
#include "Physics.h"
#include "ICollider.h"
#include <memory>
using namespace engine;

void Engine::Awake()
{
	CreateWindow(800, 800, "Simple Engine");
}

void Engine::Start()
{
	auto rect = CreateObject(Rectangle(Vector2f(), Vector2f(0.1, 0.1), Color::White));
	auto otherRect = CreateObject(Rectangle(Vector2f(0, -300), Vector2f(0.1, 0.1), Color::White));
	rect->AddComponent(std::make_shared<Components::Physics>(rect->GetTransform()));
	rect->AddComponent(std::make_shared<Components::Colliders::Box>(rect->GetTransform()));
	otherRect->AddComponent(std::make_shared<Components::Colliders::Box>(otherRect->GetTransform()));
	auto vec = engine::Vector2f::Zero;
}

void Engine::Update()
{
}
