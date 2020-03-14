#ifndef TUTORIAL
#define TUTORIAL

#include "game_item.h"
#include "renderer.h"
#include "texture.h"
#include <SDL2/SDL.h>

class Tutorial : public GameItem
{
public:
  Tutorial(Renderer*, Texture*, SDL_Rect sRect, SDL_Rect dRect);
  ~Tutorial();
  void update();
  void draw();
};

#endif
