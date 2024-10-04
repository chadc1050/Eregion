#pragma once

#include "eregion/Asset/Shader.h"
#include "eregion/Asset/Texture.h"
#include "eregion/Core/Result.h"

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