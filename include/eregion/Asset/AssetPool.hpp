#pragma once

#include "eregion/Asset/Loader.hpp"
#include "eregion/Asset/Shader.hpp"
#include "eregion/Asset/Texture.hpp"
#include "eregion/Core/Result.hpp"
#include "eregion/Logger/Logger.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace eregion {

class AssetPool {
  public:
    static AssetPool& getInstance();
    static Result<Shader> getShader(std::string path);
    static Result<Texture> getTexture(std::string path);

    // Delete copy constructor and assignment operator to prevent copying
    AssetPool(const AssetPool&) = delete;
    AssetPool& operator=(const AssetPool&) = delete;

  private:
    AssetPool();
    ~AssetPool() = default;

    std::unordered_map<std::string, Shader> shaderPool;
    std::unordered_map<std::string, Texture> texturePool;
};
} // namespace eregion