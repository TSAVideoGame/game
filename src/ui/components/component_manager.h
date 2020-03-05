#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include "item_manager.h"
#include "renderer.h"

class ComponentManager : public ItemManager
{
public:
  ComponentManager(Renderer* ren);
  ~ComponentManager();
  void update();
  void draw();
};

#endif
