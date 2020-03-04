#ifndef SCORE
#define SCORE

#include "game_item.h"
#include "item_manager.h"
#include "renderer.h"
#include <SDL2/SDL.h>

class Score : public GameItem, public ItemManager
{
public:
  Score(Renderer*, int* score, int x, int y, int w);
  ~Score();
  void update();
  void draw();
  void goTo(int x, int y);
private:
  int* score;
  SDL_Rect myPos;
};

#endif
