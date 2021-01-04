#include "./constants.hpp"
#include "./game.hpp"

int main() {

  // Initialize
  Game &game = Game::GetGame();
  game.Initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

  while (game.IsRunning()) {
    game.Update();
    game.Render();
  }

  return 0;
}
