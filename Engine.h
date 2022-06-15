#include "Window.h"
#include "Utility.h"
#include "Object.h"
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

