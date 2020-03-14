#ifndef BOSS
#define BOSS

#include "game_item.h"
#include "renderer.h"
#include "player.h"
#include "item_manager.h"
#include "texture.h"

class Boss : public GameItem, public ItemManager
{
public:
  Boss(Renderer*, Texture*, Player*);
  ~Boss();
  void update();
  void draw();
private:
  int health;
  Player* player;
  int ticks;
  bool dir; // True = right, False = left
  int animationState;
};

#endif
