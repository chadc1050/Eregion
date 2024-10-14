#include "eregion/Asset/AssetPool.hpp"

using namespace eregion;

namespace eregion {

AssetPool& AssetPool::getInstance() {
    // Guaranteed to be destroyed
    static AssetPool instance;
    return instance;
}

Result<Shader> AssetPool::getShader(std::string path) {

    AssetPool& inst = AssetPool::getInstance();

    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    std::string id = name + extension;

    if (inst.shaderPool.contains(id)) {
        info("Cache hit for shader: " + id);
        return Result<Shader>(Success<Shader>(inst.shaderPool[id]));
    }

    auto res = loadShader(path);

    if (res.isError()) {
        return Result<Shader>(Error{"Could not load shader!"});
    }

    Shader shader = res.getValue();

    // Put into cache
    inst.shaderPool[id] = shader;

    info("Successfully loaded shader: " + id);
    return Result<Shader>(Success<Shader>(shader));
}

Result<Texture*> AssetPool::getTexture(std::string path) {

    AssetPool& inst = AssetPool::getInstance();

    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    std::string id = name + extension;

    if (inst.texturePool.contains(id)) {
        info("Cache hit for texture: " + id);
        return Result<Texture*>(Success<Texture*>(inst.texturePool[id]));
    }

    auto res = loadTexture(path);

    if (res.isError()) {
        return Result<Texture*>(Error{"Could not load texture!"});
    }

    Texture* texture = res.getValue();

    // Put into cache
    inst.texturePool[id] = texture;

    info("Successfully loaded texture: " + id);
    return Result<Texture*>(Success<Texture*>(texture));
}

AssetPool::AssetPool() {}
} // namespace eregion