#include <iostream>

#include "pixel.h"

int main(void)
{
	pixel::CreateWindow(800, 600, "Pixel Demo v0.1");

	while (pixel::WindowShouldClose() == false)
	{
		pixel::ClearBackground(pixel::RED);
		pixel::EndDrawing();
	}

	return 0;
}