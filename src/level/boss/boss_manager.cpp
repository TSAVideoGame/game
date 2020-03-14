#include "boss_manager.h"
#include "game_states.h"
#include "game.h"
#include "boss.h"

BossManager::BossManager(Renderer* ren, Player* p) : ItemManager(ren)
{
  player = p;
  texture = new Texture("res/images/bosses/boss_small.png", renderer);
}

BossManager::~BossManager()
{

}

void BossManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
  }

  if (Game::gameState.getState() == GameState::LEVEL)
  {
    if (Game::levelInfo.cutScene && objects.size() < 1)
    {
      objects.push_back(new Boss(renderer, texture, player));
    }
  }

  ItemManager::update();
}
