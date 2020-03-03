#ifndef LEVEL_SELECT_MANAGER
#define LEVEL_SELECT_MANAGER

#include "item_manager.h"
#include "renderer.h"
#include "level_tile.h"

class LevelSelectManager : public ItemManager
{
public:
  LevelSelectManager(Renderer*);
  ~LevelSelectManager();
  void update();
  void switchSelected(LevelTile*);
private:
  void saveGame();
};

#endif
