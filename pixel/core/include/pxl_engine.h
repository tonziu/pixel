#ifndef H_PIXEL_ENGINE
#define H_PIXEL_ENGINE

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace pixel
{
	typedef struct Engine
	{
		GLFWwindow* window;
		int target_fps;
		double time_previous;
	} Engine;
}

#endif // H_PIXEL_ENGINE
