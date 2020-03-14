#include "label_manager.h"
#include "renderer.h"
#include "score_manager.h"
#include "game_states.h"
#include "game.h"
#include "label.h"
#include "constants.h"

/*
 * Sets the x position of the labels
 */
static int labelLocation(int pos)
{
  return (WINDOW_WIDTH / 2 - 64) + (pos * 512) - (Game::levelInfo.level * 512) + 192;
}

LabelManager::LabelManager(Renderer* ren) : ItemManager(ren)
{

}

LabelManager::~LabelManager()
{

}

void LabelManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    if (Game::gameState.getState() == GameState::MENU)
    {
      for (int i = 0; i < 6; i++)
        objects.push_back(new Label(renderer, {448, i * 32, 64, 32}, {labelLocation(i), -128, 64, 32}));
    }
    else if (Game::gameState.getState() == GameState::LEVEL)
    {
      objects.push_back(new Label(renderer, {0, 96, 320, 34}, {14, 16, 320, 34})); // Player health label
      objects.push_back(new Label(renderer, {0, 130, 320, 39}, {14, 61, 320, 37})); // Time label
    }
    objects.push_back(new ScoreManager(renderer));
  }

  if (Game::gameState.getState() == GameState::MENU)
  {
    for (int i = 0; i < objects.size() - 2; i++)
    {
      if (Game::scores[i])
        dynamic_cast<Label*>(objects[i])->setSrc({448, i * 32, 64, 32}); // Colored key
      else
        // dynamic_cast<Label*>(objects[i])->setSrc({448, 160, 64, 32}); // Black key
        dynamic_cast<Label*>(objects[i])->setSrc({0, 0, 0, 0}); // Show no key

      if (i == Game::levelInfo.level)
        dynamic_cast<Label*>(objects[i])->goTo(labelLocation(i), WINDOW_HEIGHT / 2 - 256);
      else
        dynamic_cast<Label*>(objects[i])->goTo(labelLocation(i), -128);
    }
  }

  ItemManager::update();
}
