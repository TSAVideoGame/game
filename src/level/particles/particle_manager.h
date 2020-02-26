#ifndef PARTICLE_MANAGER
#define PARTICLE_MANAGER

#include "item_manager.h"
#include "renderer.h"

class ParticleManager : public ItemManager
{
public:
  ParticleManager(Renderer*);
  ~ParticleManager();
  void update();
private:
  int ticks;
};

#endif
