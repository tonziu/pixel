#include "pxl_font.h"

#include "glad/glad.h"

#include <stdexcept>
#include <iostream>

namespace pixel
{
    bool Font::Initialize(const std::string& font_path, int font_size)
    {
        m_FontSize = font_size;

        if (FT_Init_FreeType(&m_Ft))
        {
            std::cerr << "Error(Font): Could not initialize FreeType Library.\n";
            return false;
        }

        if (FT_New_Face(m_Ft, font_path.c_str(), 0, &m_Face))
        {
            std::cerr << "Error(Font): Could not load font: " << font_path << "\n";
            return false;
        }

        FT_Set_Pixel_Sizes(m_Face, 0, m_FontSize);

        return true;
    }

    Font::~Font()
    {
        FT_Done_Face(m_Face);
        FT_Done_FreeType(m_Ft);
    }

    const Glyph& Font::GetGlyph(char32_t character)
    {
        if (m_Glyphs.find(character) != m_Glyphs.end())
        {
            return m_Glyphs[character];
        }

        loadGlyph(character);

        return m_Glyphs[character];
    }

    void Font::loadGlyph(char32_t character)
    {
        if (FT_Load_Char(m_Face, character, FT_LOAD_RENDER))
        {
            std::cerr << "Error(Font): Could not load glyph: " << static_cast<char>(character) << '\n';
            return;
        }

        // Ensure FreeType bitmap is single-channel (grayscale)
        auto& bitmap = m_Face->glyph->bitmap;
        if (bitmap.pixel_mode != FT_PIXEL_MODE_GRAY)
        {
            std::cerr << "Error(Font): Unsupported pixel mode for glyph: " << static_cast<char>(character) << '\n';
            return;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED, // Single-channel grayscale texture
            bitmap.width,
            bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Glyph glyph =
        {
            texture,
            glm::ivec2(bitmap.width, bitmap.rows),
            glm::ivec2(m_Face->glyph->bitmap_left, m_Face->glyph->bitmap_top),
            static_cast<unsigned int>(m_Face->glyph->advance.x >> 6)
        };

        m_Glyphs[character] = glyph;
    }

    int Font::GetFontSize() const
    {
        return m_FontSize;
    }

    int Font::GetAscent() const
    {
        return m_Face->size->metrics.ascender >> 6;
    }

    int Font::GetDescent() const
    {
        return m_Face->size->metrics.descender >> 6;
    }

    int Font::GetLineSpacing() const
    {
        return m_Face->size->metrics.height >> 6;
    }
}
