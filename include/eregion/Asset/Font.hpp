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

namespace eregion {

struct Character {
    Texture* texture;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

class Font {
  public:
    static Result<Font*> compile(FT_Face face, std::string name, unsigned int fontSize);
    ~Font();

  private:
    std::unordered_map<char, Character> characters = {};
};
} // namespace eregion