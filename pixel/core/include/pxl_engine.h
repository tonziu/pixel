#ifndef H_PIXEL_ENGINE
#define H_PIXEL_ENGINE

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace pixel
{
	typedef struct Engine
	{
		GLFWwindow* window;
	} Engine;
}

#endif // H_PIXEL_ENGINE