#include "player_manager.h"
#include "player.h"
#include "game.h"

PlayerManager::PlayerManager(Renderer* ren) : ItemManager(ren)
{
  Player* p = new Player(renderer);
  objects.push_back(p);
  playerActive = false;
}

PlayerManager::~PlayerManager()
{

}

void PlayerManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    playerActive = false;
    switch (Game::gameState.getState())
    {
      case GameState::LEVEL:
      {
        dynamic_cast<Player*>(objects[0])->reset();
        playerActive = true;
      }
      break;
    }
  }

  ItemManager::update();
}

void PlayerManager::draw()
{
  if (playerActive == true)
    ItemManager::draw();
}

Player* PlayerManager::getPlayer()
{
  return dynamic_cast<Player*>(objects[0]);
}
