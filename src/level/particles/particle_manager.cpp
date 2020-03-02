#include "particle_manager.h"
#include "game_states.h"
#include "game.h"
#include "constants.h"
#include "particle.h"

ParticleManager::ParticleManager(Renderer* ren) : ItemManager(ren)
{

}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::update()
{
  if (GameStates::getFirstTick())
  {
    removeObjects();
  }

  if (GameStates::getState() == GameState::LEVEL)
  {
    ticks++;
    switch (Game::levelInfo.level)
    {
      case 0:
        break;
      case 1: // Water
      {
        if (ticks % (TARGET_FPS * 2) == 0)
          objects.push_back(new Particle(renderer, std::rand() % (WINDOW_WIDTH - 16), WINDOW_HEIGHT));
        break;
      }
      case 2: // Ice
        if (ticks % 4 == 0)
        {
          if (std::rand() % 2 == 0)
            objects.push_back(new Particle(renderer, WINDOW_WIDTH, 0 + std::rand() % WINDOW_HEIGHT));
          else
            objects.push_back(new Particle(renderer, WINDOW_WIDTH - std::rand() % WINDOW_HEIGHT, 0));
        }
        break;
      case 3:
        break;
      case 4:
        break;
    }
  }

  for (int i = objects.size() - 1; i >= 0; i--)
  {
    objects[i]->update();
    if (dynamic_cast<Particle*>(objects[i])->offScreen())
    {
      delete objects[i];
      objects.erase(objects.begin() + i);
    }
  }
}
