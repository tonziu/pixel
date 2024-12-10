#ifndef H_PIXEL
#define H_PIXEL

#include "pxl_engine.h"
#include "pxl_color.h"

namespace pixel
{
	static Engine g_Engine = {};

	bool CreateWindow(int width, int height, const char* title);

	bool WindowShouldClose();

	void ClearBackground(Color color);

	void EndDrawing();
}

#endif // H_PIXEL
