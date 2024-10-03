#pragma once

#include "eregion/Asset/Loader.h"
#include "eregion/Asset/Shader.h"
#include "eregion/Core/Result.h"
#include "eregion/Logger/Logger.h"
#include <filesystem>
#include <string>
#include <unordered_map>

namespace eregion {

class AssetPool {
  public:
    static AssetPool& getInstance();
    static Result<Shader> getShader(std::string path);

    // Delete copy constructor and assignment operator to prevent copying
    AssetPool(const AssetPool&) = delete;
    AssetPool& operator=(const AssetPool&) = delete;

  private:
    AssetPool();
    ~AssetPool() = default;

    std::unordered_map<std::string, Shader> shaderPool;
};
} // namespace eregion