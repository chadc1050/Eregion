#include "eregion/Asset/Font.hpp"

using namespace eregion;

Result<Font*> Font::compile(FT_Face face, std::string name, unsigned int fontSize) {
    // Set size to load glyphs
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    // Disable byte alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font* font = new Font();

    for (unsigned char c = 0; c < 128; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {

            return Result<Font*>(Error{"Error loading glyphs!"});
        }

        FT_Bitmap bitmap = face->glyph->bitmap;
        auto res = Texture::compile(name + "-" + std::to_string(c), bitmap.buffer, bitmap.width, bitmap.rows, 1);

        if (res.isError()) {

            return Result<Font*>(Error{"Error loading glyph bitmap texture! " + res.getError()});
        }

        Character character = {res.getValue(), glm::ivec2(bitmap.width, bitmap.rows),
                               glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                               static_cast<unsigned int>(face->glyph->advance.x)};

        font->characters[c] = character;
    }

    return Result<Font*>(Success<Font*>(font));
}

Font::~Font() {
    for (auto& pair : characters) {
        delete pair.second.texture;
    }

    characters.clear();
}