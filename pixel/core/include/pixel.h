#ifndef H_PIXEL
#define H_PIXEL

#include "pxl_engine.h"

namespace pixel
{
	static Engine g_Engine = {};

	bool CreateWindow(int width, int height, const char* title);

	bool WindowShouldClose();

	void EndDrawing();
}

#endif // H_PIXEL
