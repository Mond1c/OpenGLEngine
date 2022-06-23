#include "Window.h"
#include "Settings.h"
#include "Utility.h"
#include "Object.h"
#include "ICollider.h"
#include <memory>
#include <vector>

#pragma once
class Engine
{
private:
	std::vector<std::shared_ptr<engine::Object>> objects;
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
	template<typename T, typename = typename std::enable_if<std::is_base_of<engine::Object, T>::value>::type>
	std::shared_ptr<T> CreateObject(T&& tmp) {
		std::shared_ptr<T> obj = std::make_shared<T>(std::move(tmp));
		objects.push_back(obj);
		return obj;
	}

	template<typename T, typename G,
		typename = std::enable_if<std::is_base_of<Components::ICollider, T>::value>::type,
		typename = std::enable_if<std::is_base_of<Object, G>::value>::type>
	std::shared_ptr<T> CreateCollider(std::shared_ptr<G>& object) {
		std::shared_ptr<T> collider = std::make_shared<T>(object->GetTransform());
		object->AddComponent(collider);
		engine::Components::ALL_COLLIDERS.push_back(collider);
		return collider;
	}

	void CreateWindow(int width, int height, const char* title) {
		window = std::make_unique<engine::Window>(width, height, title);
	}
public:
	void Draw() {
		for (const auto& obj : objects) {
			obj->Draw();
		}
	}

	void Loop() {
		while (!window->ShouldClose()) {
			glClear(GL_COLOR_BUFFER_BIT);
			Update();
			for (auto& obj : objects) obj->Update();
			Draw();
			window->SwapBuffers();
			glfwPollEvents();
		}
	}
public:
	void Awake();
	void Start();
	void Update();
};

