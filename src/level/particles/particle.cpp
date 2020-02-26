#include "particle.h"
#include "game.h"
#include <cmath>
#include "constants.h"
#include <iostream>

Particle::Particle(Renderer* ren, int x, int y) : GameItem(ren)
{
  switch (Game::levelInfo.level)
  {
    case 0:
      break;
    case 1:
      srcRect = {448, 0, 16, 16};
      myPos.w = 16;
      myPos.h = 16;
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }

  myPos = {x, y, myPos.w, myPos.h};
}

Particle::~Particle()
{

}

void Particle::update()
{
  ticks++;
  switch (Game::levelInfo.level)
  {
    case 0:
      break;
    case 1:
      myPos.y--;
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
}

void Particle::draw()
{
  switch (Game::levelInfo.level)
  {
    case 0:
      break;
    case 1:
      destRect = {myPos.x + (int) (4 * std::sin(.25 * ticks)), myPos.y, myPos.w, myPos.h};
      renderer->copy(Game::getTexture()->getTexture(), &srcRect, &destRect);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
}

bool Particle::offScreen()
{
  switch (Game::levelInfo.level)
  {
    case 0:
      break;
    case 1:
      return (myPos.y + myPos.h < 0);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
  return true;
}
