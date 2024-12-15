#include <iostream>

#include "pixel.h"

int main(void)
{
	if (pixel::CreateWindow(800, 600, "Pixel Demo v0.1") == false)
	{
		std::cerr << "Error(main) : Couldn't create a Pixel Window.\n";
		return -1;
	}

	pixel::SetTargetFPS(30);

	while (pixel::WindowShouldClose() == false)
	{
		pixel::ClearBackground(pixel::LIGHTGRAY);

		pixel::EndDrawing();
	}

	pixel::CloseWindow();

	return 0;
}