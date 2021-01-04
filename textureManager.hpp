#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "./game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {
public:
  static SDL_Texture *LoadTexture(const char *fileName);
  static void Draw(SDL_Texture *texture, SDL_Rect srcrect, SDL_Rect dstrect,
                   SDL_RendererFlip flip);
};
#endif
