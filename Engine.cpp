#include "Engine.h"
#include "Physics/Physics.h"
#include "Core/Utility.h"
#include "Physics/ICollider.h"
#include "Core/Debug.h"
#include "Parser/File.h"
#include "Core/GameObject.h"
#include "Core/MonoBehaviour.h"
#include "Core/Input.h"
#include <memory>

using namespace engine;

class PlayerController : public core::MonoBehaviour {
private:
    std::shared_ptr<core::Input> input;
public:
    void Start() override {
        Debug::Log("PlayerController is starting now");
    }

public:
    PlayerController(std::shared_ptr<core::GameObject> &obj, std::shared_ptr<core::Window> &w)
            : MonoBehaviour(obj, w), input(std::make_shared<core::Input>(w)) {}

    ~PlayerController() override = default;

    void Update() override {
        if (input->IsKeyPressed(core::Input::Key::W)) {
            transform->Translate(core::Vector2f(0, 1));
        }
        if (input->IsKeyPressed(core::Input::Key::S)) {
            transform->Translate(core::Vector2f(0, -1));
        }
        if (input->IsKeyPressed(core::Input::Key::D)) {
            transform->Translate(core::Vector2f(1, 0));
        }
        if (input->IsKeyPressed(core::Input::Key::A)) {
            transform->Translate(core::Vector2f(-1, 0));
        }
    }
};

void Engine::Awake() {
    CreateWindow(800, 800, "Simple Engine");
}


void Engine::Start() {
    parser::File file("Object.object");
    OBJECTS = file.Load();
    auto &circle1 = OBJECTS[0];
    auto &circle2 = OBJECTS[1];
    circle1->AddComponent(std::make_shared<components::Physics>(circle1->GetTransform(), 5.0f));
    circle2->AddComponent(std::make_shared<components::Physics>(circle2->GetTransform(), 2.0f));
    circle1->GetComponent<components::Physics>()->SetVelocity({1.0f, -1.0f});
    circle2->GetComponent<components::Physics>()->SetVelocity({-1.0f, 1.0f});
    CreateCollider<components::colliders::Box>(circle1);
    CreateCollider<components::colliders::Box>(circle2);
    file = parser::File("test.object");
    file.Save(OBJECTS);
    OBJECTS[2]->AddComponent(std::make_shared<PlayerController>(OBJECTS[2], window));

    for (auto &obj : OBJECTS) obj->StartAllMonoBehaviourComponents();
}

void Engine::Update() {

}
