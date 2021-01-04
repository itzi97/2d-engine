#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "../entityManager.hpp"
#include "../game.hpp"
#include "./component.hpp"
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <iostream>

class TransformComponent : public Component {
public:
  glm::vec2 position;
  glm::vec2 velocity;
  int width;
  int height;
  int scale;

  TransformComponent(int posX, int posY, int velX, int velY, int w, int h,
                     int s)
      : position(glm::vec2(posX, posY)), velocity(glm::vec2(velX, velY)),
        width(w), height(h), scale(s) {}

  void Initialize() override {}

  void Update(float deltaTime) override {
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
  }

  void Render() override {
    SDL_Rect transformRectangle = {(int)position.x, (int)position.y,
                                   width * scale, height * scale};
    SDL_SetRenderDrawColor(Game::GetGame().GetRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawRect(Game::GetGame().GetRenderer(), &transformRectangle);
  }
};

#endif
