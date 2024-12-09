#include "pixel.h"

bool pixel::CreateWindow(int width, int height, const char* title)
{
	if (glfwInit() == GLFW_FALSE)
	{
		return false;
	}

	g_Engine.window = glfwCreateWindow(width, height, title, NULL, NULL);

	if (g_Engine.window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(g_Engine.window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false)
	{
		return false;
	}

	return true;
}

bool pixel::WindowShouldClose()
{
	return glfwWindowShouldClose(g_Engine.window);
}

void pixel::EndDrawing()
{
	glfwSwapBuffers(g_Engine.window);
	glfwPollEvents();
}