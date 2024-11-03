#pragma once

#include "eregion/Asset/Font.hpp"
#include "eregion/Asset/Shader.hpp"
#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Result.hpp"

#include "stb_image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace eregion {

class Loader {
  public:
    Loader();

    Result<Shader> loadShader(std::string path);
    Result<Texture*> loadTexture(std::string path);
    // TODO: Need to add font size as well
    Result<Font*> loadFont(std::string path, unsigned int fontSize);

    ~Loader();

  private:
    FT_Library ft;
};
} // namespace eregion