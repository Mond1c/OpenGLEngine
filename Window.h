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
		}
	public:
		bool ShouldClose();
		// In the future I will change the name to "Update" (maybe)
		void SwapBuffers();
	};
}

