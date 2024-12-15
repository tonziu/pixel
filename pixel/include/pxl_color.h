#ifndef H_PIXEL_COLOR
#define H_PIXEL_COLOR

namespace pixel
{
	// Pixel's color definition [RGBA]
	typedef struct Color
	{
		int r;
		int g;
		int b;
		int a;
	} Color;

	const Color RED = { 255, 0, 0, 255 };
	const Color LIGHTGRAY = { 200, 200, 200, 255 };
	const Color BLACK = { 0, 0, 0, 255 };
}

#endif // H_PIXEL_COLOR
