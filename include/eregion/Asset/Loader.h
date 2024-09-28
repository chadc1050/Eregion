#ifndef EREGION_LOADER_H
#define EREGION_LOADER_H

#include "eregion/Asset/Shader.h"
#include "eregion/Core/Result.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace eregion {

Result<Shader> loadShader(std::string absolutePath);
} // namespace eregion

#endif