#include "pxl_text_renderer.h"

#include <glad/glad.h>
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

namespace pixel
{
    bool TextRenderer::Initialize(const char* vshader_path, const char* fshader_path, int screen_width, int screen_height)
    {
        m_ScreenWidth = screen_width;
        m_ScreenHeight = screen_height;

        if (!m_Shader.Initialize(vshader_path, fshader_path))
        {
            std::cerr << "Error(TextRenderer): Could not initialize shader.\n";
            return false;
        }

        // Initialize orthogonal projection
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_ScreenWidth), static_cast<float>(m_ScreenHeight), 0.0f, -1.0f, 1.0f);
        m_Shader.Use();
        m_Shader.SetMat4("projection", projection);

        // Generate and configure VAO and VBO
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return true;
    }

    TextRenderer::~TextRenderer()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
    }

    void TextRenderer::RenderText(Font& font, const std::string& text, glm::vec2 position, float scale, glm::vec4 color)
    {
        m_Shader.Use();
        m_Shader.SetVec4("textColor", color);

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(m_VAO);

        unsigned int lastTexture = 0; // Track the last bound texture to avoid redundant binds

        for (char c : text)
        {
            const Glyph& glyph = font.GetGlyph(c);

            if (glyph.textureID != lastTexture)
            {
                glBindTexture(GL_TEXTURE_2D, glyph.textureID);
                lastTexture = glyph.textureID;
            }

            // Calculate vertex positions
            float xpos = position.x + glyph.bearing.x * scale;
            float ypos = position.y + (font.GetAscent() - glyph.bearing.y) * scale;
            float w = glyph.size.x * scale;
            float h = glyph.size.y * scale;

            // Update VBO with quad vertices
            float vertices[6][4] =
            {
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos,     ypos,       0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f }
            };

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            // Draw the character quad
            glDrawArrays(GL_TRIANGLES, 0, 6);

            // Advance the cursor for the next character
            position.x += glyph.advance * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
