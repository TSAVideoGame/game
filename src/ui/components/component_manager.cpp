#include "component_manager.h"
#include "button_manager.h"
#include "game.h"
#include "game_states.h"

ComponentManager::ComponentManager(Renderer* ren) : ItemManager(ren)
{
  ButtonManager* buttonM = new ButtonManager(ren);
  objects.push_back(buttonM);
}

ComponentManager::~ComponentManager()
{

}

void ComponentManager::update()
{
  ItemManager::update();
}

void ComponentManager::draw()
{
  if (Game::gameState.getState() == GameState::LEVEL && Game::levelInfo.paused)
  {
    renderer->setDrawColor(0, 0, 0, 128);
    renderer->fillRect(NULL);
  }
  ItemManager::draw();
}
