#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include "./entityManager.hpp"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class AssetManager {
private:
  static AssetManager *instance;
  AssetManager();

  std::map<std::string, SDL_Texture *> textures;

public:
  static AssetManager &GetAssetManager();
  ~AssetManager();
  void ClearData();
  void AddTexture(std::string textureId, const char *filePath);
  SDL_Texture *GetTexture(std::string textureId);
};

#endif
