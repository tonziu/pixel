#ifndef H_PIXEL_TEXTRENDERER
#define H_PIXEL_TEXTRENDERER

#include <string>
#include <glm/glm.hpp>

#include "pxl_shader.h"
#include "pxl_font.h"

namespace pixel
{
    class TextRenderer 
    {
    public:
        TextRenderer() = default;

        bool Initialize(const char* vshader_path, const char* fshader_path, int screen_width, int screen_height);
        ~TextRenderer();

        void RenderText(Font& font, const std::string& text, glm::vec2 position, float scale, glm::vec4 color);

    private:
        Shader m_Shader;
        unsigned int m_VAO;
        unsigned int m_VBO;

        int m_ScreenWidth;
        int m_ScreenHeight;
    };
}



#endif // H_PIXEL_TEXTRENDERER
