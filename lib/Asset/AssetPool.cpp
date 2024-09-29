#include "eregion/Asset/AssetPool.h"

using namespace eregion;

namespace eregion {

AssetPool::AssetPool() { shaderPool = std::unordered_map<std::string, Shader>(); }

Result<Shader> AssetPool::getShader(std::string path) {

    std::filesystem::path pathObj(path);

    std::string id = pathObj.stem().string();

    if (shaderPool.contains(id)) {
        return Result<Shader>(Success<Shader>(shaderPool[id]));
    }

    auto res = loadShader(path);

    if (res.isError()) {
        return Result<Shader>(Error{"Could not load shader!"});
    }

    return Result<Shader>(Success<Shader>(res.getValue()));
}

} // namespace eregion