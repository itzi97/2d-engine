#include "./textureManager.hpp"
#include <iostream>

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
  SDL_Surface *surface = IMG_Load(fileName);
  if (!surface) {
    std::cerr << "Unable to load image" << fileName << "!" << std::endl;
    std::cerr << "SDL_image Error: " << IMG_GetError() << std::endl;
  }
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(Game::GetGame().GetRenderer(), surface);
  if (!texture) {
    std::cerr << "Unable to load texture" << fileName << "!" << std::endl;
    std::cerr << "SDL_image Error: " << IMG_GetError() << std::endl;
  }
  SDL_FreeSurface(surface);
  return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect srcrect,
                          SDL_Rect dstrect, SDL_RendererFlip flip) {
  // SDL_RenderCopy(Game::GetGame().GetRenderer(), texture, &srcrect, &dstrect);
  SDL_RenderCopyEx(Game::GetGame().GetRenderer(), texture, &srcrect, &dstrect,
                   0.0, NULL, flip);
}
