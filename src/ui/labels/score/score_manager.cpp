#include "score_manager.h"
#include "game_states.h"
#include "game.h"
#include "score.h"
#include "constants.h"

static int menuScoreLocation(int pos)
{
  return (WINDOW_WIDTH / 2 - 64) + (pos * 512) - (Game::levelInfo.level * 512) - 128;
}

ScoreManager::ScoreManager(Renderer* ren) : ItemManager(ren)
{

}

ScoreManager::~ScoreManager()
{

}

void ScoreManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    switch (Game::gameState.getState())
    {
      case GameState::LEVEL:
      {
        Game::levelInfo.time = 0;
        objects.push_back(new Score(renderer, &Game::levelInfo.time, 16, 64, 16));
        break;
      }
      case GameState::MENU:
      {
        for (int i = 0; i < 7; i++)
          objects.push_back(new Score(renderer, &Game::scores[i], menuScoreLocation(i), -64, 32));
        break;
      }
      case GameState::OVER:
      {
        break;
      }
      case GameState::WIN:
      {
        Game::scores[Game::levelInfo.level] = 1; // Temporary code

        // Unlock levels 2 - 5 after beating level 1
        if (Game::levelInfo.level == 0)
          for (int i = 1; i < 5; i++)
            Game::levelsUnlocked[i] = 1;

        // If all the levels have been beaten, unlock the fifth level
        if (Game::scores[0] > 0 && Game::scores[1] > 0 && Game::scores[2] > 0 && Game::scores[3] > 0 && Game::scores[4] > 0)
          Game::levelsUnlocked[5] = 1;

        // Update time if time is faster
        if (Game::levelInfo.time < Game::times[Game::levelInfo.level])
          Game::times[Game::levelInfo.level] = Game::levelInfo.time;

        objects.push_back(new Score(renderer, &Game::times[Game::levelInfo.level], WINDOW_WIDTH / 2 - 128, WINDOW_HEIGHT / 2 - 128, 64));
        break;
      }
    }
  }

  switch (Game::gameState.getState())
  {
    case GameState::MENU:
    {
      for (int i = 0; i < objects.size() - 1; i++)
      {
        if (i == Game::levelInfo.level) // Make score onscreen
          dynamic_cast<Score*>(objects[i])->goTo(menuScoreLocation(i), WINDOW_HEIGHT / 2 - 256);
        else // Make score offscreen
          dynamic_cast<Score*>(objects[i])->goTo(menuScoreLocation(i), -64);
      }

      break;
    }
  }

  ItemManager::update();
}
