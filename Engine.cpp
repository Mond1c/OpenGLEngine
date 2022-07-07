#include "Engine.h"
#include "Physics.h"
#include "Utility.h"
#include "ICollider.h"
#include "Debug.h"
#include "File.h"
#include <memory>
using namespace engine;

void Engine::Awake()
{
	CreateWindow(800, 800, "Simple Engine");
}


void Engine::Start()
{
	File file("Object.object");
	OBJECTS = file.Load();
	auto circle1 = OBJECTS[0];
	auto circle2 = OBJECTS[1];
	circle1->AddComponent(std::make_shared<components::Physics>(circle1->GetTransform(), 5.0f));
	circle2->AddComponent(std::make_shared<components::Physics>(circle2->GetTransform(), 2.0f));
	circle1->GetComponent<components::Physics>()->SetVelocity({ 1.0f, -1.0f });
	circle2->GetComponent<components::Physics>()->SetVelocity({ -1.0f, 1.0f });
	CreateCollider<components::colliders::Circle>(circle1);
	CreateCollider<components::colliders::Box>(circle2);
	file = File("test.object");
	file.Save(OBJECTS);
}

void Engine::Update()
{
}
