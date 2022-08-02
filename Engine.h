#pragma once
#include "Window.h"
#include "Settings.h"
#include "Utility.h"
#include "GameObject.h"
#include "ICollider.h"
#include <memory>
#include <vector>
#include <future>

class Engine
{
private:
	std::vector<std::shared_ptr<engine::GameObject>> OBJECTS;
	std::unique_ptr<engine::Window> window;
	float framesPerSecond = 0;
	float curTime;
	float lastTime = 0;
	float FPS = 0;
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

	void CalculateFrameRate() {
		++framesPerSecond;
		curTime = glfwGetTime();
		if (curTime - lastTime > 1.0f) {
			lastTime = curTime;
			FPS = framesPerSecond;
			framesPerSecond = 0;
		}
	}
public:

	void Draw(std::vector<std::future<void>>& threads) {
		for (const auto& obj : OBJECTS) {
			engine::Vector2f position = obj->GetPosition();
			if (position.x <= 1 && position.x >= -1 && position.y <= 1 && position.y >= -1) {
				threads.push_back(std::async(std::launch::async, &engine::GameObject::Draw, obj.get()));
				obj->Draw();
			}
		}
		threads.clear();
	}

	void Loop() {
		std::vector<std::future<void>> threads;
		static double limitFPS = 1.0 / 60.0;
		double lastTime = glfwGetTime();
		double time = lastTime;
		double delta = 0, curTime = 0;
		int updates = 0;
		int frames = 0;
		while (!window->ShouldClose()) {
			curTime = glfwGetTime();
			glClear(GL_COLOR_BUFFER_BIT);
			delta += (curTime - lastTime) / limitFPS;
			lastTime = curTime;
			//engine::Debug::Log(delta);
			if (delta >= 1.0) {
				Update();
				for (auto& obj : OBJECTS) {
					threads.push_back(std::async(
						std::launch::async,
						&engine::GameObject::Update,
						obj.get()));
				}
				threads.clear();
				--delta;
				++updates;
			}
			Draw(threads);
			window->SwapBuffers();
			frames++;
			if (glfwGetTime() - time > 1) {
				++time;
				std::string str = "Updates: " + std::to_string(updates) + ", " + "Frames: " + std::to_string(frames);
				window->SetTitle(str);
				//engine::Debug::Log("Updates: " + std::to_string(updates) + ", " + "Frames: " + std::to_string(frames));
				updates = frames = 0;
			}
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

