#include "rocket.h"
#include "renderer.h"
#include "player.h"
#include "game.h"
#include "constants.h"
#include <SDL2/SDL.h>

static int maxVel = 10;

Rocket::Rocket(Renderer* ren, Player* p, int x, int y, int dir) : GameItem(ren)
{
  xVel = 0;
  yVel = 0;
  player = p;
  direction = dir;
  switch (direction)
  {
    case 0:
      srcRect = {224, 32, 32, 64};
      destRect = {x, y, 32, 64};
      break;
    case 1:
      srcRect = {192, 32, 32, 64};
      destRect = {x, y, 32, 64};
      break;
    case 2:
      srcRect = {192, 0, 64, 32};
      destRect = {x, y, 64, 32};
      break;
    case 3:
      srcRect = {256, 0, 64, 32};
      destRect = {x, y, 64, 32};
      break;
  }
}

Rocket::~Rocket()
{

}

void Rocket::update()
{
  // Player collides with top
  if ((player->getDelta().y + player->getDelta().h <= destRect.y && player->getPos().y + player->getPos().h >= destRect.y) &&
      ((player->getPos().x >= destRect.x && player->getPos().x <= destRect.x + destRect.w) ||
      (player->getPos().x + player->getPos().w >= destRect.x && player->getPos().x + player->getPos().w <= destRect.x + destRect.w)))
    player->hit(0, destRect.y - (player->getPos().y + player->getPos().h), EnemyTypes::boss);

  // Player collides with bottom
  if ((player->getDelta().y >= destRect.y + destRect.h && player->getPos().y <= destRect.y + destRect.h) &&
      ((player->getPos().x >= destRect.x && player->getPos().x <= destRect.x + destRect.w) ||
      (player->getPos().x + player->getPos().w >= destRect.x && player->getPos().x + player->getPos().w <= destRect.x + destRect.w)))
    player->hit(1, player->getPos().y - (destRect.y + destRect.h), EnemyTypes::boss);

  // Player collides with left
  if ((player->getDelta().x + player->getDelta().w <= destRect.x && player->getPos().x + player->getPos().w >= destRect.x) &&
      ((player->getPos().y >= destRect.y && player->getPos().y <= destRect.y + destRect.h) ||
      (player->getPos().y + player->getPos().h >= destRect.y && player->getPos().y + player->getPos().h <= destRect.y + destRect.h)))
    player->hit(2, (player->getPos().x + player->getPos().w) - destRect.x, EnemyTypes::boss);

  // Player collides with right
  if ((player->getDelta().x >= destRect.x + destRect.w && player->getPos().x <= destRect.x + destRect.w) &&
      ((player->getPos().y >= destRect.y && player->getPos().y <= destRect.y + destRect.h) ||
      (player->getPos().y + player->getPos().h >= destRect.y && player->getPos().y + player->getPos().h <= destRect.y + destRect.h)))
    player->hit(3, (destRect.x + destRect.w) - player->getPos().x, EnemyTypes::boss);

  switch (direction) {
    case 0:
      if (-yVel < maxVel)
        yVel--;
      break;
    case 1:
      if (yVel < maxVel)
        yVel++;
      break;
    case 2:
      if (-xVel < maxVel)
        xVel--;
      break;
    case 3:
      if (xVel < maxVel)
        xVel++;
      break;
  }
  destRect.x += xVel;
  destRect.y += yVel;
}

void Rocket::draw()
{
  SDL_Rect dRect = {destRect.x, destRect.y - Game::camera.y, destRect.w, destRect.h};
  renderer->copy(GameItem::texture->getTexture(), &srcRect, &dRect);
}

bool Rocket::isOffScreen()
{
  switch (direction)
  {
    case 0: // Up
      return destRect.y < Game::camera.y;
    case 1: // Down
      return destRect.y + destRect.h > Game::camera.y + WINDOW_HEIGHT;
    case 2: // Left
      return destRect.x < 0;
    case 3: // Right
      return destRect.x + destRect.w > WINDOW_WIDTH;
  }
  return true; // Shouldn't reach here, object should be deleted
}
