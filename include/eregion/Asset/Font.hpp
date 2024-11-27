#pragma once

#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Result.hpp"

#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace eregion {

struct Character {
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
    glm::vec2 uvStart;
    glm::vec2 uvEnd;
};

class Font {
  public:
    static Result<Font*> compile(FT_Face face, std::string name, unsigned int fontSize);
    Texture* getTexture();
    Character getCharacter(char character);

    ~Font();

  private:
    std::string name;
    std::unordered_map<char, Character> characters = {};
    Texture* texture;

    static const unsigned short ASCII_RANGE = 128;
};
} // namespace eregion