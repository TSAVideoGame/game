#ifndef BACKGROUND_MANAGER
#define BACKGROUND_MANAGER

#include "item_manager.h"
#include "mixer.h"
#include "player_manager.h"

class BackgroundManager : public ItemManager
{
public:
  BackgroundManager(Renderer*, PlayerManager*);
  ~BackgroundManager();
  void update();
private:
  Mixer* mix;
  PlayerManager* playerM;
};

#endif
