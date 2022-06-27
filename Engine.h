#pragma once
#include "Window.h"
#include "Settings.h"
#include "Utility.h"
#include "GameObject.h"
#include "ICollider.h"
#include <memory>
#include <vector>

class Engine
{
	std::vector<std::shared_ptr<engine::GameObject>> OBJECTS;
	std::unique_ptr<engine::Window> window;
public:
	Engine() = default;
	Engine(Engine&) = delete;
	Engine(Engine&&) = delete;
public:
	~Engine() {
		glfwTerminate();
	}
public:
	Engine& operator=(Engine&) = delete;
	Engine& operator=(Engine&&) = delete;
private:
	void CreateWindow(int width, int height, const char* title) {
		window = std::make_unique<engine::Window>(width, height, title);
	}
public:
	void Draw() {
		for (const auto& obj : OBJECTS) {
			engine::Vector2f position = obj->GetPosition();
			if (position.x <= 1 && position.x >= -1 && position.y <= 1 && position.y >= -1)
				obj->Draw();
		}
	}

	void Loop() {
		while (!window->ShouldClose()) {
			glClear(GL_COLOR_BUFFER_BIT);
			Update();
			for (auto& obj : OBJECTS) obj->Update();
			Draw();
			window->SwapBuffers();
			glfwPollEvents();
		}
	}
private:
	template<typename T, typename = typename std::enable_if<std::is_base_of<engine::GameObject, T>::value>::type>
	std::shared_ptr<engine::GameObject> CreateObject(T&& tmp) {
		std::shared_ptr<T> obj = std::make_shared<T>(std::move(tmp));
		OBJECTS.push_back(obj);
		return obj;
	}

	template<typename T, typename G,
		typename = std::enable_if<std::is_base_of<components::ICollider, T>::value>::type,
		typename = std::enable_if<std::is_base_of<GameObject, G>::value>::type>
	std::shared_ptr<T> CreateCollider(std::shared_ptr<G>& object) {
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

