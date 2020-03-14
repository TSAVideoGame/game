#include "particle.h"
#include "game.h"
#include <cmath>
#include "constants.h"
#include <iostream>

Particle::Particle(Renderer* ren, int x, int y) : GameItem(ren)
{
  switch (Game::levelInfo.level)
  {
    case LEVEL_GRASS:
      break;
    case LEVEL_WATER:
      srcRect = {256, 32, 16, 16};
      myPos.w = 16;
      myPos.h = 16;
      break;
    case LEVEL_ICE:
      myPos.w = 4 + std::rand() % 12;
      myPos.h = myPos.w;
      break;
    case LEVEL_SPACE:
      break;
    case LEVEL_VOLCANO:
      break;
  }

  myPos = {x, y, myPos.w, myPos.h};
}

Particle::~Particle()
{

}

void Particle::update()
{
  if (!Game::levelInfo.paused)
  {
    ticks++;
    switch (Game::levelInfo.level)
    {
      case LEVEL_GRASS:
        break;
      case LEVEL_WATER:
        myPos.y--;
        break;
      case LEVEL_ICE:
        myPos.x--;
        myPos.y++;
        break;
      case LEVEL_SPACE:
        break;
      case LEVEL_VOLCANO:
        break;
    }
  }
}

void Particle::draw()
{
  switch (Game::levelInfo.level)
  {
    case LEVEL_GRASS:
      break;
    case LEVEL_WATER:
      destRect = {myPos.x + (int) (4 * std::sin(.25 * ticks)), myPos.y, myPos.w, myPos.h};
      renderer->copy(Game::getTexture(), &srcRect, &destRect);
      break;
    case LEVEL_ICE:
      destRect = {myPos.x + (int) (4 * std::sin(.25 * ticks)), myPos.y + (int) (4 * std::sin(.25 * ticks)), myPos.w, myPos.h};
      renderer->setDrawColor(255, 255, 255, 128);
      renderer->fillRect(&destRect);
      break;
    case LEVEL_SPACE:
      break;
    case LEVEL_VOLCANO:
      break;
  }
}

bool Particle::offScreen()
{
  switch (Game::levelInfo.level)
  {
    case LEVEL_GRASS:
      break;
    case LEVEL_WATER:
      return (myPos.y + myPos.h < 0);
      break;
    case LEVEL_ICE:
      return (myPos.y > WINDOW_HEIGHT || myPos.x < 0);
      break;
    case LEVEL_SPACE:
      break;
    case LEVEL_VOLCANO:
      break;
  }
  return true;
}
