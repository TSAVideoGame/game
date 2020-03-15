#include "trampoline_manager.h"
#include "game_states.h"
#include "game.h"
#include "constants.h"
#include "trampoline.h"
#include <cstdlib>
#include <ctime>

static int maxTramps = 5;

TrampolineManager::TrampolineManager(Renderer* ren, Player* p) : ItemManager(ren)
{
  player = p;
  std::srand(std::time(nullptr));
  lastTrampY = 0;
  ticks = 0;
}

TrampolineManager::~TrampolineManager()
{

}

void TrampolineManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    switch (Game::gameState.getState())
    {
      case GameState::LEVEL:
      {
        ticks = 0;
        maxReached = false;
        lastTrampY = 0;
        maxTramps = 5;
        if (Game::levelInfo.level == LEVEL_GRASS)
        {
          objects.push_back(new Trampoline(renderer, player, 0, WINDOW_HEIGHT - 48, WINDOW_WIDTH));
          objects.push_back(new Trampoline(renderer, player, 0, 0, WINDOW_WIDTH));
          objects.push_back(new Trampoline(renderer, player, 0, -WINDOW_HEIGHT, WINDOW_WIDTH));
          objects.push_back(new Trampoline(renderer, player, 0, -WINDOW_HEIGHT * 2, WINDOW_WIDTH));
          objects.push_back(new Trampoline(renderer, player, 0, -WINDOW_HEIGHT * 3, WINDOW_WIDTH));
        }
        else
        {
          objects.push_back(new Trampoline(renderer, player, 0, WINDOW_HEIGHT - 48, WINDOW_WIDTH));
          objects.push_back(new Trampoline(renderer, player, std::rand() % WINDOW_WIDTH - (WINDOW_WIDTH / 8), WINDOW_HEIGHT / 2, std::rand() % 512 + 512));
        }
      }
      break;
    }
  }

  if (Game::gameState.getState() == GameState::LEVEL && !Game::levelInfo.paused)
  {
    // Increase difficulty
    if (-Game::levelInfo.maxHeight / 2000 > Game::levelInfo.difficulty)
      Game::levelInfo.difficulty = -Game::levelInfo.maxHeight / 2000;

    // Add new trampolines
    if (Game::levelInfo.difficulty < Game::levelInfo.maxDifficulty)
    {
      // Prevent trampoline spwaning in the tutorial
      if ((Game::levelInfo.level == LEVEL_GRASS && -Game::levelInfo.maxHeight > WINDOW_HEIGHT * 3) || Game::levelInfo.level != LEVEL_GRASS)
      {
        if (objects.size() > maxTramps)
          objects.pop_front();
        if (lastTrampY - Game::levelInfo.maxHeight > 256 * Game::levelInfo.difficulty)
        {
          int x = std::rand() % WINDOW_WIDTH - (WINDOW_WIDTH / (8 * Game::levelInfo.difficulty));
          int y = Game::camera.y;
          int w = (-10 * Game::levelInfo.difficulty + 128) + (std::rand() % (-50 * Game::levelInfo.difficulty + 512)); // The random range is x + rand() % y
          objects.push_back(new Trampoline(renderer, player, x, y, w));
          lastTrampY = Game::camera.y;
        }
      }
    }
    else
    {
      if (!maxReached)
      {
        objects.push_back(new Trampoline(renderer, player, 0, Game::camera.y, WINDOW_WIDTH));
        maxReached = true;
      }
    }
  }

  for (auto tramp : objects)
    tramp->update();
}

void TrampolineManager::draw()
{
  for (auto tramp : objects)
    tramp->draw();
}

void TrampolineManager::removeObjects()
{
  for (auto obj : objects)
    delete obj;
  std::deque<Trampoline*>().swap(objects);
}
