#include "eregion/Asset/Font.hpp"

using namespace eregion;

Result<Font*> Font::compile(FT_Face face, std::string name, unsigned int fontSize) {
    // Set size to load glyphs
    FT_Set_Pixel_Sizes(face, 0, fontSize);

    // Disable byte alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    Font* font = new Font();

    int atlasWidth = 0;
    int atlasHeight = 0;
    std::vector<FT_Bitmap> bitmaps(ASCII_RANGE);
    std::vector<glm::ivec2> bitmapOffsets(ASCII_RANGE);

    for (unsigned char c = 0; c < ASCII_RANGE; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {

            return Result<Font*>(Error{"Error loading glyphs!"});
        }

        FT_Bitmap bitmap = face->glyph->bitmap;
        bitmaps[c] = bitmap;

        // Adding 1 for padding
        atlasWidth += bitmap.width + 1;
        atlasHeight = std::max(atlasHeight, static_cast<int>(bitmap.rows));

        bitmapOffsets[c] = {face->glyph->bitmap_left, face->glyph->bitmap_top};
    }

    // Create the texture atlas
    unsigned char* atlasBuffer = new unsigned char[atlasWidth * atlasHeight]();
    int xOffset = 0;

    for (unsigned char c = 0; c < ASCII_RANGE; c++) {
        FT_Bitmap& bitmap = bitmaps[c];

        for (int y = 0; y < bitmap.rows; y++) {
            for (int x = 0; x < bitmap.width; x++) {
                atlasBuffer[(y * atlasWidth) + xOffset + x] = bitmap.buffer[y * bitmap.pitch + x];
            }
        }

        Character character = {glm::ivec2(bitmap.width, bitmap.rows), bitmapOffsets[c],
                               static_cast<unsigned int>(face->glyph->advance.x),
                               glm::vec2(static_cast<float>(xOffset) / atlasWidth, 0.0f),
                               glm::vec2(static_cast<float>(xOffset + bitmap.width) / atlasWidth, 1.0f)};

        font->characters[c] = character;

        // Adding 1 for padding
        xOffset += bitmap.width + 1;
    }

    auto res = Texture::compile(name, atlasBuffer, atlasWidth, atlasHeight, 1);

    delete[] atlasBuffer;

    if (res.isError()) {

        return Result<Font*>(Error{"Error loading glyph bitmap texture! " + res.getError()});
    }

    font->texture = res.getValue();
    font->name = name;

    return Result<Font*>(Success<Font*>(font));
}

Texture* Font::getTexture() { return texture; }

Character Font::getCharacter(char character) { return characters[character]; }

Font::~Font() {
    delete texture;

    characters.clear();
}