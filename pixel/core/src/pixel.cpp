#include "pixel.h"

#include <iostream>

constexpr int DEFAULT_TARGET_FPS = 60;

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

	g_Engine.target_fps = DEFAULT_TARGET_FPS;

	g_Engine.time_previous = glfwGetTime();

	glfwSwapInterval(0);

	return true;
}

bool pixel::WindowShouldClose()
{
	return glfwWindowShouldClose(g_Engine.window);
}

void pixel::EndDrawing()
{
	glfwPollEvents();

	while (glfwGetTime() < g_Engine.time_previous + 1.0 / g_Engine.target_fps) 
	{
	}

	glfwSwapBuffers(g_Engine.window);
	g_Engine.time_previous += 1.0 / g_Engine.target_fps;
}

void pixel::ClearBackground(Color color)
{
	glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void pixel::CloseWindow()
{
	if (g_Engine.window)
	{
		glfwDestroyWindow(g_Engine.window);
	}

	glfwTerminate();
}

void pixel::SetTargetFPS(int fps)
{
	g_Engine.target_fps = fps;
}