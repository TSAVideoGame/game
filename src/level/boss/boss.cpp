#include "boss.h"
#include "game_states.h"
#include "game.h"
#include "constants.h"
#include "rocket.h"
#include <SDL2/SDL.h>

Boss::Boss(Renderer* ren, Player* p) : GameItem(ren), ItemManager(ren)
{

  destRect = {WINDOW_WIDTH / 2 - 256, Game::camera.y - 128 * 3, 512, 256};
  health = 10;
  player = p;

  switch (Game::levelInfo.level)
  {
    case 0:
    {
      srcRect = {0, 231, 512, 256};
      break;
    }
    case 1:
    {
      srcRect = {0, 231, 512, 256};
      break;
    }
    case 2:
    {
      srcRect = {0, 231, 512, 256};
      break;
    }
    case 3:
    {
      srcRect = {0, 231, 512, 256};
      break;
    }
    case 4:
    {
      srcRect = {0, 231, 512, 256};
      break;
    }
  }
}

Boss::~Boss()
{

}

void Boss::update()
{
  if (GameStates::getState() == GameState::LEVEL)
  {
    if (Game::levelInfo.cutSceneOver && !Game::levelInfo.paused)
    {
      ticks++;

      // Player collides with top
      if ((player->getDelta().y + player->getDelta().h <= destRect.y && player->getPos().y + player->getPos().h >= destRect.y) &&
          ((player->getPos().x >= destRect.x && player->getPos().x <= destRect.x + destRect.w) ||
          (player->getPos().x + player->getPos().w >= destRect.x && player->getPos().x + player->getPos().w <= destRect.x + destRect.w)))
        player->hit(0, destRect.y - (player->getPos().y + player->getPos().h), EnemyTypes::boss);

      // Player collides with bottom
      if ((player->getDelta().y >= destRect.y + destRect.h && player->getPos().y <= destRect.y + destRect.h) &&
          ((player->getPos().x >= destRect.x && player->getPos().x <= destRect.x + destRect.w) ||
          (player->getPos().x + player->getPos().w >= destRect.x && player->getPos().x + player->getPos().w <= destRect.x + destRect.w)))
      {
        // Risky way to deal more damage
        player->hit(1, player->getPos().y - (destRect.y + destRect.h), EnemyTypes::boss);
        health -= 2;
      }

      // Player collides with left
      if ((player->getDelta().x + player->getDelta().w <= destRect.x && player->getPos().x + player->getPos().w >= destRect.x) &&
          ((player->getPos().y >= destRect.y && player->getPos().y <= destRect.y + destRect.h) ||
          (player->getPos().y + player->getPos().h >= destRect.y && player->getPos().y + player->getPos().h <= destRect.y + destRect.h)))
      {
        if (player->isBoosting())
          health--;
        player->hit(2, (player->getPos().x + player->getPos().w) - destRect.x, EnemyTypes::boss);
      }

      // Player collides with right
      if ((player->getDelta().x >= destRect.x + destRect.w && player->getPos().x <= destRect.x + destRect.w) &&
          ((player->getPos().y >= destRect.y && player->getPos().y <= destRect.y + destRect.h) ||
          (player->getPos().y + player->getPos().h >= destRect.y && player->getPos().y + player->getPos().h <= destRect.y + destRect.h)))
      {
        if (player->isBoosting())
          health--;
        player->hit(3, (destRect.x + destRect.w) - player->getPos().x, EnemyTypes::boss);
      }

      // Unique boss behaviors based on level
      switch (Game::levelInfo.level)
      {
        case 0:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4) == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w / 2, destRect.y, 1));

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case 1:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4) == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y, 1));

          // Rockets
          if (ticks % (TARGET_FPS * 8) == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w, destRect.y, 1));

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case 2:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % TARGET_FPS * 4 == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w / 2, destRect.y, 1));

          if (ticks % TARGET_FPS * 5 == 0)
          {
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w, destRect.y + destRect.h / 2, 3));
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y + destRect.h / 2, 2));
          }

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case 3:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4) < 16)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + (ticks % (TARGET_FPS * 4)) * 32, destRect.y, 1));

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case 4:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4 )== 0)
          {
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y, 1));
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w, destRect.y, 1));
          }

          if (ticks % TARGET_FPS * 5 == 0)
          {
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y + destRect.h / 2, 3));
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y + destRect.h / 2, 2));
          }

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
      }

      if (health <= 0)
        GameStates::changeState(GameState::WIN);

      for (int i = objects.size() - 1; i >= 0; i--)
      {
        objects[i]->update();
        if (dynamic_cast<Rocket*>(objects[i])->isOffScreen())
        {
          delete objects[i];
          objects.erase(objects.begin() + i);
        }
      }
    }
    else
    {
      if (Game::levelInfo.cutScene)
      {
        dir = rand() % 2;
        if (destRect.y != Game::camera.y + 48)
          destRect.y += ((Game::camera.y + 16) - destRect.y) / 8;
      }
    }
  }
}

void Boss::draw()
{
  SDL_Rect dRect = {destRect.x, destRect.y - Game::camera.y, destRect.w, destRect.h};
  GameItem::renderer->copy(GameItem::texture->getTexture(), &srcRect, &dRect);

  // Draw health
  SDL_Rect healthBar = {WINDOW_WIDTH - (WINDOW_WIDTH / 2) - 16, 16, (int) ((WINDOW_WIDTH / 2) * (health / 20.0)), 16};
  if (health > 10)
    GameItem::renderer->setDrawColor(0x3e, 0x89, 0x48, 255);
  else if (health > 5)
    GameItem::renderer->setDrawColor(0xfe, 0xea, 0x34, 255);
  else
    GameItem::renderer->setDrawColor(0xe4, 0x3b, 0x44, 255);
  GameItem::renderer->fillRect(&healthBar);

  ItemManager::draw();
}
