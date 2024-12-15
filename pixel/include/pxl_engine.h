#ifndef H_PIXEL_ENGINE
#define H_PIXEL_ENGINE

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "pxl_color.h"

namespace pixel
{
	typedef struct Engine
	{
		GLFWwindow* window;
		int target_fps;
		double time_previous;
	} Engine;

	static Engine g_Engine = {};

	bool CreateWindow(int width, int height, const char* title);

	void CloseWindow();

	bool WindowShouldClose();

	void ClearBackground(Color color);

	void EndDrawing();

	void SetTargetFPS(int fps);

}

#endif // H_PIXEL_ENGINE
