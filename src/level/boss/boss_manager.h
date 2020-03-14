#ifndef BOSS_MANAGER
#define BOSS_MANAGER

#include "item_manager.h"
#include "renderer.h"
#include "player.h"
#include "texture.h"

class BossManager : public ItemManager
{
public:
  BossManager(Renderer*, Player*);
  ~BossManager();
  void update();
private:
  Player* player;
  Texture* texture;
};

#endif
