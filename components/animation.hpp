#ifndef ANIMATION
#define ANIMATION

class Animation {
public:
  unsigned int index;
  unsigned int numFrames;
  unsigned int animationSpeed;
  Animation(){};
  Animation(unsigned int index, unsigned int numFrames,
            unsigned int animationSpeed)
      : index(index), numFrames(numFrames), animationSpeed(animationSpeed){};
};
#endif
