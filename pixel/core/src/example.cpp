#include <iostream>

#include "pixel.h"

int main(void)
{
	pixel::CreateWindow(800, 600, "Pixel Demo v0.1");

	while (pixel::WindowShouldClose() == false)
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		pixel::EndDrawing();
	}

	return 0;
}