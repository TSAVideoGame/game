#include "tutorial_manager.h"
#include "game.h"
#include "constants.h"
#include "trampoline.h"
#include "texture.h"
#include "tutorial.h"

TutorialManager::TutorialManager(Renderer* ren) : ItemManager(ren)
{
  texture = new Texture("res/images/instructions.png", renderer);
}

TutorialManager::~TutorialManager()
{
  delete texture;
}

void TutorialManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    if (Game::levelInfo.level == LEVEL_GRASS)
    {
      objects.push_back(new Tutorial(renderer, texture, {0, 0, 1200, 180}, {WINDOW_WIDTH / 2 - 600, WINDOW_HEIGHT / 2 - 90, 1200, 180}));
      objects.push_back(new Tutorial(renderer, texture, {0, 180, 1200, 180}, {WINDOW_WIDTH / 2 - 600, -WINDOW_HEIGHT / 2 - 90, 1200, 180}));
      objects.push_back(new Tutorial(renderer, texture, {0, 360, 1200, 120}, {WINDOW_WIDTH / 2 - 600, -WINDOW_HEIGHT * 3 / 2 - 90, 1200, 120}));
      objects.push_back(new Tutorial(renderer, texture, {0, 480, 1200, 280}, {WINDOW_WIDTH / 2 - 600, -WINDOW_HEIGHT * 5 / 2 - 90, 1200, 280}));
    }
    else
      removeObjects();
  }

  ItemManager::update();
}
