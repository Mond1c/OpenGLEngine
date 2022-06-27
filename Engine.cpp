#include "Engine.h"
#include "Physics.h"
#include "ICollider.h"
#include "Debug.h"
#include <memory>
using namespace engine;

void Engine::Awake()
{
	CreateWindow(800, 800, "Simple Engine");
}


void Engine::Start()
{
	auto circle1 = CreateObject(Circle(Vector2f(), 50, Color::White));
	auto circle2 = CreateObject(Circle(Vector2f(300, -300), 50, Color::White));
	circle1->AddComponent(std::make_shared<components::Physics>(circle1->GetTransform(), 5.0f));
	circle2->AddComponent(std::make_shared<components::Physics>(circle2->GetTransform(), 2.0f));
	circle1->GetComponent<components::Physics>()->SetVelocity({ 0.1f, -0.1f });
	circle2->GetComponent<components::Physics>()->SetVelocity({ -0.1f, 0.1f });
	CreateCollider<components::colliders::Circle>(circle1);
	CreateCollider<components::colliders::Circle>(circle2);
}

void Engine::Update()
{
}
