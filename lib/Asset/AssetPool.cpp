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

    auto res = inst.loader->loadShader(path);

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

    auto res = inst.loader->loadTexture(path);

    if (res.isError()) {
        return Result<Texture*>(Error{"Could not load texture!"});
    }

    Texture* texture = res.getValue();

    // Put into cache
    inst.texturePool[id] = texture;

    info("Successfully loaded texture: " + id);
    return Result<Texture*>(Success<Texture*>(texture));
}

Result<Font*> AssetPool::getFont(std::string path, unsigned int fontSize) {

    AssetPool& inst = AssetPool::getInstance();

    std::filesystem::path pathObj(path);

    std::string name = pathObj.stem().string();
    std::string extension = pathObj.extension().string();

    std::string id = name + extension + "-" + std::to_string(fontSize);

    if (inst.fontPool.contains(id)) {
        info("Cache hit for font: " + id);
        return Result<Font*>(Success<Font*>(inst.fontPool[id]));
    }

    auto res = inst.loader->loadFont(path, fontSize);

    if (res.isError()) {
        return Result<Font*>(Error{"Could not load font!"});
    }

    Font* font = res.getValue();

    // Put into cache
    inst.fontPool[id] = font;

    info("Successfully loaded font: " + id);
    return Result<Font*>(Success<Font*>(font));
}

AssetPool::AssetPool() {}

AssetPool::~AssetPool() { delete loader; }
} // namespace eregion