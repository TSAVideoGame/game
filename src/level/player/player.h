#ifndef PLAYER
#define PLAYER

#include "game_item.h"
#include "renderer.h"
#include <SDL2/SDL.h>
#include <deque>

enum class EnemyTypes {enemy, boss, rocket};

class Player : public GameItem
{
public:
  Player(Renderer*);
  ~Player();
  void update();
  void draw();
  SDL_Rect getPos();
  SDL_Rect getDelta();
  void setPos(int x, int y);
  void hit(int dir, int change, EnemyTypes);
  int getMaxYVel();
  void reset();
  bool isBoosting() {return boosting;}
private:
  SDL_Rect delta;
  std::deque<SDL_Rect> deltas;
  float yVel, xVel;
  // TODO: Clean up this code
  bool jumping, canJump, shouldJump;
  int defMinMaxYVel, defMaxMaxYVel;
  int maxYVel, maxXVel;
  int ticks, trampTicks, airTicks, sideTicks;
  bool boosting, canBoost;
  int boostTicks, boostDir;
  int health;
  bool flipping, canFlip;
  int flipTicks;
};

#endif
