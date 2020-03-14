#include "enemy_manager.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "constants.h"

EnemyManager::EnemyManager(Renderer* ren, Player* p) : ItemManager(ren)
{
  ticks = 0;
  player = p;
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::update()
{
  if (Game::gameState.getFirstTick())
    removeObjects();

  if (Game::gameState.getState() == GameState::LEVEL)
  {
    if (!Game::levelInfo.cutScene && !Game::levelInfo.cutSceneOver && !Game::levelInfo.paused)
    {
      ticks++;
      if (ticks % 96 == 0 && Game::levelInfo.difficulty != Game::levelInfo.maxDifficulty)
      {
        objects.push_back(new Enemy(renderer, player, (std::rand() % (WINDOW_HEIGHT * 3)) + (Game::camera.y - WINDOW_HEIGHT * 3)));
      }
    }

    if (Game::levelInfo.cutScene)
      removeObjects();
  }

  for (int i = objects.size() - 1; i >= 0; i--)
  {
    objects[i]->update();
    if (dynamic_cast<Enemy*>(objects[i])->offScreen())
    {
      delete objects[i];
      objects.erase(objects.begin() + i);
    }
  }
}
