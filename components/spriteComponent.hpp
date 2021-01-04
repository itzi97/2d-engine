#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "../assetManager.hpp"
#include "../textureManager.hpp"
#include "./animation.hpp"
#include "./component.hpp"
#include "./transformComponent.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
private:
  SDL_Texture *texture;
  SDL_Rect srcrect;
  SDL_Rect dstrect;
  bool isAnimated;
  int numFrames;
  int animationSpeed;
  bool isFixed;

  std::map<std::string, Animation> animations;
  std::string currentAnimationName;
  unsigned int animationIndex = 0;

  TransformComponent *transform;

public:
  SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

  SpriteComponent(std::string assetTextureId)
      : isAnimated(false), isFixed(false) {
    SetTexture(assetTextureId);
  }

  SpriteComponent(std::string id, int numFrames, int animationSpeed,
                  bool hasDirections, bool isFixed)
      : isAnimated(true), numFrames(numFrames), animationSpeed(animationSpeed),
        isFixed(isFixed) {

    if (hasDirections) {
      Animation downAnimation = Animation(0, numFrames, animationSpeed);
      Animation rightAnimation = Animation(1, numFrames, animationSpeed);
      Animation leftAnimation = Animation(2, numFrames, animationSpeed);
      Animation upAnimation = Animation(3, numFrames, animationSpeed);

      animations.emplace("DownAnimation", downAnimation);
      animations.emplace("RightAnimation", rightAnimation);
      animations.emplace("LeftAnimation", leftAnimation);
      animations.emplace("UpAnimation", upAnimation);

      this->animationIndex = 0;
      this->currentAnimationName = "DownAnimation";
    } else {
      Animation singleAnimation = Animation(0, numFrames, animationSpeed);
      animations.emplace("SingleAnimation", singleAnimation);
      this->animationIndex = 0;
      this->currentAnimationName = "SingleAnimation";
    }

    Play(this->currentAnimationName);
    SetTexture(id);
  }

  void SetTexture(std::string assetTextureId) {

    texture = AssetManager::GetAssetManager().GetTexture(assetTextureId);
  }

  void Play(std::string animationName) {
    numFrames = animations[animationName].numFrames;
    animationIndex = animations[animationName].index;
    animationSpeed = animations[animationName].animationSpeed;
    currentAnimationName = animationName;
  }

  void Initialize() override {
    transform = owner->GetComponent<TransformComponent>();
    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = transform->width;
    srcrect.h = transform->height;
    std::cout << "size: (" << srcrect.w << "," << srcrect.h << ")" << std::endl;
  }

  void Update(float deltaTime) override {
    if (isAnimated) {
      srcrect.x = srcrect.w * ((SDL_GetTicks() / animationSpeed) % numFrames);
      srcrect.y = animationIndex * transform->height;
    }

    dstrect.x = static_cast<int>(transform->position.x);
    dstrect.y = static_cast<int>(transform->position.y);
    dstrect.w = transform->width * transform->scale;
    dstrect.h = transform->height * transform->scale;
  }

  void Render() override {
    TextureManager::Draw(texture, srcrect, dstrect, spriteFlip);
  }
};
#endif
