#ifndef BACKGROUND
#define BACKGROUND

#include "game_item.h"
#include "player.h"

class Background : public GameItem
{
public:
  Background(Renderer*, const char* imagePath);
  Background(Renderer*, const char* imagePath, int w, Player*);
  ~Background();

  void update();
  void draw();
  void setXY(int x, int y);
private:
  int width;
  Player* player;
  int ticks;
};

#endif
