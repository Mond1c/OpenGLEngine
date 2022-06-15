#pragma once
#include <GLFW/glfw3.h>
#include <exception>

namespace engine {
	class Window
	{
	private:
		GLFWwindow* window;
	public:
		Window(int width, int height, const char* title) {
			window = glfwCreateWindow(width, height, title, NULL, NULL);
			if (!window) {
				glfwTerminate();
				throw std::exception("Can't create a window");
			}
			glfwMakeContextCurrent(window);
			glViewport(0.0f, 0.0f, width, height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
		}
	public:
		Window(Window&) = delete;
		Window(Window&&) = delete;
	public:
		Window& operator=(Window&) = delete;
		Window& operator=(Window&&) = delete;
	public:
		bool ShouldClose();
		// In the future I will change the name to "Update" (maybe)
		void SwapBuffers();
	};
}

