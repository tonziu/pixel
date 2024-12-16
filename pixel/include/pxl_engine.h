#ifndef H_PIXEL_ENGINE
#define H_PIXEL_ENGINE

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "pxl_color.h"
#include "pxl_text_renderer.h"

namespace pixel
{
	typedef struct Engine
	{
		GLFWwindow* window;
		int target_fps;
		double time_previous;
		Font font;
		TextRenderer text_renderer;
	} Engine;

	static Engine g_Engine = {};

	bool CreateWindow(int width, int height, const char* title);

	void CloseWindow();

	bool WindowShouldClose();

	void ClearBackground(Color color);

	void EndDrawing();

	void SetTargetFPS(int fps);

	void DrawText(std::string text, int posx, int posy, int text_size, Color color);
}

#endif // H_PIXEL_ENGINE
