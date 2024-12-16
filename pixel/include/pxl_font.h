#ifndef H_PIXEL_FONT
#define H_PIXEL_FONT

#include <map>
#include <string>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H



namespace pixel
{
    struct Glyph 
    {
        unsigned int textureID;  // OpenGL texture ID for the glyph
        glm::ivec2 size;         // Glyph size (width, height)
        glm::ivec2 bearing;      // Offset from baseline to top-left
        unsigned int advance;    // Offset to the next character
    };

    class Font 
    {
    public:
        Font() = default;

        bool Initialize(const std::string& font_path, int font_size);

        ~Font();

        const Glyph& GetGlyph(char32_t character);

        int GetFontSize() const;
        int GetAscent() const;
        int GetDescent() const;
        int GetLineSpacing() const;

    private:
        void loadGlyph(char32_t character);

        FT_Face m_Face;                // FreeType face object
        FT_Library m_Ft;        // FreeType library object
        std::map<char32_t, Glyph> m_Glyphs; // Glyph cache
        int m_FontSize;                // Font size in pixels
    };
}


#endif // H_PIXEL_FONT
