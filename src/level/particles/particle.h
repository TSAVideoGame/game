#ifndef PARTICLE
#define PARTICLE

#include "game_item.h"
#include "renderer.h"
#include <SDL2/SDL.h>

class Particle : public GameItem
{
public:
  Particle(Renderer*, int x, int y);
  ~Particle();
  void update();
  void draw();
  bool offScreen();
  SDL_Rect myPos;
private:
  int ticks;
};

#endif
