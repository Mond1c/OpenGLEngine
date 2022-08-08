#pragma once

#include "Core/Window.h"
#include "Core/Settings.h"
#include "Core/Utility.h"
#include "Core/GameObject.h"
#include "Physics/ICollider.h"
#include <memory>
#include <vector>
#include <future>

class Engine {
private:
    inline static Engine* instance;

    std::vector<std::shared_ptr<engine::core::GameObject>> OBJECTS;
    std::shared_ptr<engine::core::Window> window;
    double framesPerSecond{};
    double curTime{};
    double lastTime{};
    inline static const double maxUpdates = 60.0;
    inline static const double limitFPS = 1.0 / maxUpdates;
private:
    Engine() = default;
public:
    static Engine* GetInstance() {
        if (instance) return instance;
        return new Engine();
    }

    Engine(Engine &) = delete;
    Engine(Engine &&) = delete;
public:
    ~Engine() {
        glfwTerminate();
    }

public:
    Engine &operator=(Engine &) = delete;

    Engine &operator=(Engine &&) = delete;

private:
    void CreateWindow(int width, int height, const char *title) {
        window = std::make_shared<engine::core::Window>(width, height, title);
    }

public:
    void Draw(std::vector<std::future<void>> &threads) {
        for (const auto &obj : OBJECTS) {
            engine::core::Vector2f position = obj->GetPosition();
            if (position.x <= 1 && position.x >= -1 && position.y <= 1 && position.y >= -1) {
                threads.push_back(std::async(std::launch::async, &engine::core::GameObject::Draw, obj.get()));
                obj->Draw();
            }
        }
        threads.clear();
    }

    void Loop() {
        std::vector<std::future<void>> threads;
        lastTime = glfwGetTime();
        double time = lastTime;
        double delta = 0;
        curTime = 0;
        int updates = 0;
        int frames = 0;
        while (!window->ShouldClose()) {
            curTime = glfwGetTime();
            glClear(GL_COLOR_BUFFER_BIT);
            delta += (curTime - lastTime) / limitFPS;
            lastTime = curTime;
            if (delta >= 1.0) {
                Update();
                for (auto &obj : OBJECTS) {
                    threads.push_back(std::async(
                            std::launch::async,
                            &engine::core::GameObject::Update,
                            obj.get()));
                }
                threads.clear();
                Draw(threads);
                window->SwapBuffers();
                --delta;
                ++updates;
            }
            frames++;
            if (glfwGetTime() - time > 1) {
                ++time;
                std::string str = "Updates: " + std::to_string(updates) + ", " + "Frames: " + std::to_string(frames);
                window->SetTitle(str);
                updates = frames = 0;
            }
            glfwPollEvents();
        }
    }

public:
    template<typename T, typename = typename std::enable_if<std::is_base_of<engine::core::GameObject, T>::value>::type>
    std::shared_ptr<engine::core::GameObject> CreateObject(T &&tmp) {
        std::shared_ptr<T> obj = std::make_shared<T>(std::move(tmp));
        OBJECTS.push_back(obj);
        return obj;
    }

    template<typename T, typename G,
            typename = typename std::enable_if<std::is_base_of<engine::components::ICollider, T>::value>::type,
            typename = typename std::enable_if<std::is_base_of<engine::core::GameObject, G>::value>::type>
    std::shared_ptr<T> CreateCollider(std::shared_ptr<G> &object) {
        std::shared_ptr<T> collider = std::make_shared<T>(object);
        object->AddComponent(collider);
        engine::components::ALL_COLLIDERS.push_back(collider);
        return collider;
    }

public:
    void Awake();

    void Start();

    void Update();
};


