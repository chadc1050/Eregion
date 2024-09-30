#include "eregion/Asset/AssetPool.h"

using namespace eregion;

namespace eregion {

AssetPool& AssetPool::getInstance() {
    // Guaranteed to be destroyed
    static AssetPool instance;
    return instance;
}

Result<Shader> AssetPool::getShader(std::string path) {

    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    std::string id = name + extension;

    if (shaderPool.contains(id)) {
        printf("Cache hit for shader: %s\n", id.c_str());
        return Result<Shader>(Success<Shader>(shaderPool[id]));
    }

    auto res = loadShader(path);

    if (res.isError()) {
        return Result<Shader>(Error{"Could not load shader!"});
    }

    Shader shader = res.getValue();

    // Put into cache
    shaderPool[id] = shader;

    printf("Successfully loaded shader: %s\n", id.c_str());
    return Result<Shader>(Success<Shader>(shader));
}

AssetPool::AssetPool() { shaderPool = std::unordered_map<std::string, Shader>(); }
} // namespace eregion