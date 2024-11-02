#include "eregion/Asset/Font.hpp"

using namespace eregion;

Font::Font(FT_Face face, std::string name) {
    // Set size to load glyphs
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {

            throw std::runtime_error("Error loading glyph.");
        }

        FT_Bitmap bitmap = face->glyph->bitmap;
        auto res = Texture::compile(name + "-" + std::to_string(c), bitmap.buffer, bitmap.width, bitmap.rows, 1);

        if (res.isError()) {

            throw std::runtime_error("Error loading glyph.");
        }

        Character character = {res.getValue(), glm::ivec2(bitmap.width, bitmap.rows),
                               glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                               static_cast<unsigned int>(face->glyph->advance.x)};

        characters[c] = character;
    }
}

Font::~Font() {
    for (auto& pair : characters) {
        delete pair.second.texture;
    }

    characters.clear();
}