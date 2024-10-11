#pragma once

#include "eregion/Asset/Shader.hpp"
#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Result.hpp"

#include "stb_image.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace eregion {

Result<Shader> loadShader(std::string path);
Result<Texture> loadTexture(std::string path);
} // namespace eregion