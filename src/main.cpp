#include "constants.h"
#include "game.h"

int main(int argc, char* args[])
{
  const int frameDelay = 1000 / TARGET_FPS;

  Uint32 frameStart;
  int frameTime;

  Game::init("The Lady and the Trampoline", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

  while (Game::isRunning())
  {
    frameStart = SDL_GetTicks();

    Game::input();
    Game::update();
    Game::draw();

    frameTime = SDL_GetTicks() - frameStart;

    while (frameDelay > frameTime)
    {
      Game::input();
      frameTime = SDL_GetTicks() - frameStart;
    }
  }

  Game::close();

  return 0;
}

// Currently loses 12,457 bytes
