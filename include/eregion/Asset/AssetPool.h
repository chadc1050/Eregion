#ifndef EREGION_ASSETPOOL_H
#define EREGION_ASSETPOOL_H

#include "eregion/Asset/Loader.h"
#include "eregion/Asset/Shader.h"
#include "eregion/Core/Result.h"
#include <filesystem>
#include <string>
#include <unordered_map>

namespace eregion {

class AssetPool {
  public:
    AssetPool();
    Result<Shader> getShader(std::string path);

  private:
    std::unordered_map<std::string, Shader> shaderPool;
};
} // namespace eregion

#endif