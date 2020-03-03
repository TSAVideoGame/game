#include "score_manager.h"
#include "game_states.h"
#include "game.h"
#include "number.h"
#include "constants.h"

ScoreManager::ScoreManager(Renderer* ren) : ItemManager(ren)
{
  texture = new Texture("res/images/numbers.png", renderer);
}

ScoreManager::~ScoreManager()
{
  delete texture;
}

void ScoreManager::update()
{
  if (GameStates::getFirstTick())
  {
    removeObjects();
    if (GameStates::getState() == GameState::LEVEL)
      Game::levelInfo.time = 0;
  }

  switch (GameStates::getState())
  {
    case GameState::LEVEL:
    {
      addDigits(Game::levelInfo.time, 0, 64, 16);
      break;
    }
    case GameState::OVER:
    {
      break;
    }
    case GameState::WIN:
    {
      Game::scores[Game::levelInfo.level] = 1;

      if (Game::levelInfo.level == 0)
      {
        for (int i = 1; i < 5; i++)
          Game::levelsUnlocked[i] = 1;
      }

      if (Game::scores[0] > 0 && Game::scores[1] > 0 && Game::scores[2] > 0 && Game::scores[3] > 0 && Game::scores[4] > 0)
      {
        Game::levelsUnlocked[5] = 1;
      }

      if (Game::levelInfo.time < Game::times[Game::levelInfo.level])
        Game::times[Game::levelInfo.level] = Game::levelInfo.time;

      addDigits(Game::times[Game::levelInfo.level], WINDOW_WIDTH / 2 - 128, WINDOW_HEIGHT / 2 - 128, 64);
      break;
    }
  }

  ItemManager::update();
}

void ScoreManager::addDigits(int num, int x, int y, int w)
{
  int a = num;
  int digits = 0;
  while (a != 0)
  {
    a /= 10;
    digits++;
  }
  if (digits == 0)
    digits = 1;
  while (objects.size() < digits)
  {
    objects.push_back(new Number(renderer, texture, (w * (objects.size() + 1)) + x, y, (objects.size() + 1)));
  }
}
