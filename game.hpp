#ifndef GAME_HPP
#define GAME_HPP

#include "./assetManager.hpp"
#include "./components/component.hpp"
#include "./entity.hpp"
#include "./entityManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game {
private:
  static Game *instance;
  Game();

  bool isRunning;
  int screenWidth, screenHeight;

  AssetManager &assetManager;
  EntityManager &entityManager;

  // SDL variables
  SDL_Window *window;
  SDL_Renderer *renderer;

public:
  ~Game();

  static Game &GetGame();

  void LoadLevel(int levelNumber);
  void Initialize(unsigned int screenWidth, unsigned int screenHeight);
  void Update();
  void Render();

  bool IsRunning() const;

  SDL_Renderer *GetRenderer();
};

#endif
