#include "level_manager.h"
#include "game.h"
#include "boss_manager.h"
#include "cutscene_manager.h"
#include "enemy_manager.h"
#include "particle_manager.h"
#include "player_manager.h"
#include "trampoline_manager.h"
#include "tutorial_manager.h"
#include "constants.h"

static void resetLevel()
{
  // Reset Level Information
  Game::levelInfo.cutScene = false;
  Game::levelInfo.cutSceneOver = false;
  Game::levelInfo.difficulty = 1;
  Game::levelInfo.maxHeight = 0;
  Game::levelInfo.time = 0;
  Game::levelInfo.bossDefeated = false;
}

LevelManager::LevelManager(Renderer* ren, PlayerManager* pM) : ItemManager(ren)
{
  playerM = pM;
  ticks = 0;
}

LevelManager::~LevelManager()
{

}

void LevelManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    switch (Game::gameState.getState())
    {
      case GameState::LEVEL:
      {
        resetLevel();

        BossManager* bossM = new BossManager(renderer, playerM->getPlayer());
        objects.push_back(bossM);

        EnemyManager* enemyM = new EnemyManager(renderer, playerM->getPlayer());
        objects.push_back(enemyM);

        TrampolineManager* trampolineM = new TrampolineManager(renderer, playerM->getPlayer());
        objects.push_back(trampolineM);

        TutorialManager* tutorialM = new TutorialManager(renderer);
        objects.push_back(tutorialM);
      }
      break;
    }
  }

  if (Game::gameState.getState() == GameState::LEVEL && !Game::levelInfo.paused)
  {
    // Increase Time
    if (!Game::levelInfo.cutScene)
    {
      ticks++;
      if (ticks % TARGET_FPS == 0 && Game::levelInfo.time < 999)
        Game::levelInfo.time++;
    }
  }

  ItemManager::update();
}

void LevelManager::draw()
{
  for (int i = objects.size() - 1; i >= 0; i--)
    objects[i]->draw();
}
