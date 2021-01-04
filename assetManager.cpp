#include "./assetManager.hpp"
#include "./textureManager.hpp"

AssetManager *AssetManager::instance = nullptr;

AssetManager::AssetManager(){};

AssetManager &AssetManager::GetAssetManager() {
  if (!instance)
    instance = new AssetManager();
  return *instance;
}

AssetManager::~AssetManager() { this->ClearData(); }

void AssetManager::ClearData() { textures.clear(); }

void AssetManager::AddTexture(std::string textureId, const char *filePath) {
  textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture *AssetManager::GetTexture(std::string textureId) {
  return textures[textureId];
}
