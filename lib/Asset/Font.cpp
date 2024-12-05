#include "eregion/Asset/Font.hpp"

using namespace eregion;

Result<Font*> Font::compile(FT_Face face, std::string name, unsigned int fontSize) {
    // Set size to load glyphs
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    Font* font = new Font();

    auto atlasWidth = ASCII_RANGE * fontSize;
    auto atlasHeight = fontSize;

    std::vector<unsigned char> buffer(atlasWidth * atlasHeight, 0);

    int off = 0;

    for (unsigned char c = 0; c < ASCII_RANGE; c++) {

        FT_UInt idx = FT_Get_Char_Index(face, c);

        if (idx == 0) {
            error("Character not found in font: " + std::to_string(c));
            continue;
        }

        if (FT_Load_Glyph(face, idx, FT_LOAD_RENDER)) {
            error("Could not load character: " + std::to_string(c));
            continue;
        }

        FT_Bitmap bitmap = face->glyph->bitmap;

        for (unsigned int y = 0; y < bitmap.rows; y++) {
            for (unsigned int x = 0; x < bitmap.width; x++) {
                // Need to invert the y range to get it to flip vertically
                buffer[(bitmap.rows - 1 - y) * atlasWidth + off + x] = bitmap.buffer[x + bitmap.width * y];
            }
        }

        unsigned int advance = face->glyph->advance.x >> 6;

        Character character = {
            glm::ivec2(bitmap.width, bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(advance), glm::vec2(static_cast<float>(off) / atlasWidth, 0.0f),
            glm::vec2(static_cast<float>(off + bitmap.width) / atlasWidth, 1.0f)};

        font->characters[c] = character;

        off += advance;
    }

    TextureOptions options =
        TextureOptions{MinFilter::LINEAR, MagFilter::LINEAR, Wrap::CLAMP_TO_EDGE, Wrap::CLAMP_TO_EDGE};

    auto res = Texture::compile(name, buffer.data(), atlasWidth, atlasHeight, 1, options);

    if (res.isError()) {

        return Result<Font*>(Error{"Error loading glyph bitmap texture! " + res.getError()});
    }

    font->texture = res.getValue();
    font->name = name;

    return Result<Font*>(Success<Font*>(font));
}

Texture* Font::getTexture() { return texture; }

Character Font::getCharacter(char character) { return characters[static_cast<unsigned char>(character)]; }

Font::~Font() {
    delete texture;

    characters.clear();
}

Font::Font() { characters.reserve(ASCII_RANGE); }