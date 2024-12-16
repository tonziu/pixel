#include "pixel.h"
#include "pxl_engine.h"

#include <iostream>

constexpr int DEFAULT_TARGET_FPS = 60;
constexpr int DEFAULT_FONT_SIZE = 32;

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

	if (g_Engine.font.Initialize("..\\res\\fonts\\press-start-2p\\PressStart2P-vaV7.ttf", DEFAULT_FONT_SIZE) == false)
	{
		std::cerr << "Error(Engine): Couldn't initialize the default font.\n";
		return false;
	}

	if (g_Engine.text_renderer.Initialize("..\\res\\shaders\\pxl_text_vshader.glsl", "..\\res\\shaders\\pxl_text_fshader.glsl", width, height) == false)
	{
		std::cerr << "Error(Engine): Couldn't initialize the text renderer.\n";
		return false;
	}

	glViewport(0, 0, width, height);

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

void pixel::DrawText(std::string text, int posx, int posy, int text_size, Color color)
{
	glm::vec4 text_color = glm::vec4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	glm::vec2 text_pos = glm::vec2(posx, posy);
	double scale = text_size / (float)DEFAULT_FONT_SIZE;
	g_Engine.text_renderer.RenderText(g_Engine.font, text, text_pos, scale, text_color);
}