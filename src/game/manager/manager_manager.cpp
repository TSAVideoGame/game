#include "manager_manager.h"
#include "background_manager.h"
#include "slide_manager.h"
#include "menu_manager.h"
#include "component_manager.h"
#include "trampoline_manager.h"
#include "player_manager.h"
#include "enemy_manager.h"
#include "cutscene_manager.h"
#include "boss_manager.h"
#include "label_manager.h"
#include "particle_manager.h"

/*
 * It updates in the order here,
 * but draws in the reverse order
 */

ManagerManager::ManagerManager(Renderer* renderer)
{
  objects.reserve(10);

  CutSceneManager* cutSceneM = new CutSceneManager(renderer);
  objects.push_back(cutSceneM);

  ParticleManager* particleM = new ParticleManager(renderer);
  objects.push_back(particleM);

  LabelManager* labelM = new LabelManager(renderer);
  objects.push_back(labelM);

  PlayerManager* playerM = new PlayerManager(renderer);
  objects.push_back(playerM);

  BossManager* bossM = new BossManager(renderer, playerM->getPlayer());
  objects.push_back(bossM);

  EnemyManager* enemyM = new EnemyManager(renderer, playerM->getPlayer());
  objects.push_back(enemyM);

  TrampolineManager* trampolineM = new TrampolineManager(renderer, playerM->getPlayer());
  objects.push_back(trampolineM);

  ComponentManager* componentM = new ComponentManager(renderer);
  objects.push_back(componentM);

  MenuManager* menuM = new MenuManager(renderer);
  objects.push_back(menuM);

  SlideManager* slideM = new SlideManager(renderer);
  objects.push_back(slideM);

  BackgroundManager* backgroundM = new BackgroundManager(renderer);
  objects.push_back(backgroundM);
}

ManagerManager::~ManagerManager()
{

}

void ManagerManager::draw()
{
  for (int i = objects.size() - 1; i >= 0; i--)
  {
    objects[i]->draw();
  }
}
