#include "./game.hpp"
#include "./components/spriteComponent.hpp"
#include "./components/transformComponent.hpp"
#include "./constants.hpp"
#include <glm/glm.hpp>
#include <iostream>

// TODO: GLOBALS PLEASE DELETE

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(100.0f, 100.0f);

Game *Game::instance = nullptr;

Game &Game::GetGame() {
  if (!instance)
    instance = new Game();
  return *instance;
}

Game::Game()
    : window(nullptr), renderer(nullptr),
      assetManager(AssetManager::GetAssetManager()),
      entityManager(EntityManager::GetEntityManager()) {}

Game::~Game() {
  // Clear data from entities
  entityManager.ClearData();

  // Empty SDL2 data
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_Quit();
  std::cout << "Game is destroyed" << std::endl;
}

void Game::LoadLevel(int levelNumber) {
  // Load the textures
  std::cout << "Load textures" << std::endl;
  assetManager.AddTexture(
      "ninja-jump",
      std::string("./assets/imgs/Main Characters/Pink Man/Fall (32x32).png")
          .c_str());
  assetManager.AddTexture(
      "ninja-idle",
      std::string("./assets/imgs/Main Characters/Pink Man/Idle (32x32).png")
          .c_str());
  assetManager.AddTexture(
      "ninja-run",
      std::string("./assets/imgs/Main Characters/Pink Man/Run (32x32).png")
          .c_str());

  // TODO: Get peter to show up
  std::cout << "Load peter" << std::endl;
  Entity &peter(entityManager.AddEntity("peter"));
  peter.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 4);
  peter.AddComponent<SpriteComponent>("ninja-jump");
  Entity &alex(entityManager.AddEntity("alex"));
  alex.AddComponent<TransformComponent>(screenWidth, 0, -20, 20, 32, 32, 4);
  alex.AddComponent<SpriteComponent>("ninja-idle", 11, 90, false, false);
  Entity &franklin(entityManager.AddEntity("franklin"));
  franklin.AddComponent<TransformComponent>(0, screenHeight, 20, -20, 32, 32,
                                            4);
  franklin.AddComponent<SpriteComponent>("ninja-run", 12, 90, false, false);
}

void Game::Initialize(unsigned int screenWidth, unsigned int screenHeight) {
  SDL_Init(SDL_INIT_EVERYTHING);

  this->screenWidth = screenWidth;
  this->screenHeight = screenHeight;

  // Create window
  this->window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, this->screenWidth,
                                  this->screenHeight, SDL_WINDOW_BORDERLESS);

  // Check that the window was successfully created
  if (!window) {
    // In the case that the window could not be made...
    std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
    return;
  }

  this->renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    // In the case that the window renderer could not be made...
    std::cerr << "Could not create window renderer: " << SDL_GetError()
              << std::endl;
    return;
  }

  this->isRunning = true;

  std::cout << "Game is initailized" << std::endl;

  LoadLevel(1);

  entityManager.ListAllEntities();
}

void Game::Update() {

  // Processing input
  SDL_Event event;

  while (SDL_PollEvent(&event) > 0) {
    switch (event.type) {
    case SDL_QUIT: {
      std::cout << "Quitting application\n";
      isRunning = false;
      break;
    }
    case SDL_KEYDOWN: {
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
    }
    default: {
      break;
    }
    }
  }

  // Store ticks passed from last frame statically
  static float ticksLastFrame = 0;

  int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

  // Wait until 16ms (for 60FPS)
  if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
    SDL_Delay(timeToWait);
  }

  // Delta time (difference in ticks from last frame converted to seconds)
  float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

  // Clamp deltaTime to a maximum value
  deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

  ticksLastFrame = SDL_GetTicks();

  // Update
  entityManager.Update(deltaTime);
}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
  SDL_RenderClear(renderer);

  if (entityManager.HasNoEntities()) {
    return;
  }

  entityManager.Render();

  SDL_RenderPresent(renderer);
}

bool Game::IsRunning() const { return isRunning; }

SDL_Renderer *Game::GetRenderer() { return renderer; }
