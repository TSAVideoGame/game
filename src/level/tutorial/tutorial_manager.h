#ifndef TUTORIAL_MANAGER
#define TUTORIAL_MANAGER

#include "renderer.h"
#include "item_manager.h"
#include "texture.h"

class TutorialManager : public ItemManager
{
public:
  TutorialManager(Renderer*);
  ~TutorialManager();
  void update();
private:
  Texture* texture;
};

#endif
