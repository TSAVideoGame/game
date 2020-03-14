#ifndef LEVEL_MANAGER
#define LEVEL_MANAGER

#include "item_manager.h"
#include "renderer.h"
#include "player_manager.h"

class LevelManager : public ItemManager
{
public:
   LevelManager(Renderer*, PlayerManager*);
   ~LevelManager();
   void update();
   void draw();
 private:
   PlayerManager* playerM;
};

#endif
