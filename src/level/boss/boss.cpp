#include "boss.h"
#include "game.h"
#include "constants.h"
#include "rocket.h"
#include <SDL2/SDL.h>

Boss::Boss(Renderer* ren, Texture* text, Player* p) : GameItem(ren), ItemManager(ren)
{
  texture = text;
  destRect = {WINDOW_WIDTH / 2 - 256, Game::camera.y - 128 * 3, 512, 256};
  health = 20;
  player = p;
  animationState = 0;
  ticks = 0;

  switch (Game::levelInfo.level)
  {
    case LEVEL_GRASS:
    {
      srcRect = {0, 0, 32, 16};
      break;
    }
    case LEVEL_WATER:
    {
      srcRect = {32, 0, 32, 16};
      break;
    }
    case LEVEL_ICE:
    {
      srcRect = {64, 0, 32, 16};
      break;
    }
    case LEVEL_SPACE:
    {
      srcRect = {96, 0, 32, 16};
      break;
    }
    case LEVEL_VOLCANO:
    {
      srcRect = {128, 0, 32, 16};
      break;
    }
    case LEVEL_CASTLE:
    {
      srcRect = {0, 0, 256, 64};
      break;
    }
  }
}

Boss::~Boss()
{

}

void Boss::update()
{
  if (Game::gameState.getState() == GameState::LEVEL)
  {
    ticks++;
    if (Game::levelInfo.cutSceneOver && !Game::levelInfo.paused && !Game::levelInfo.bossDefeated)
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
        case LEVEL_GRASS:
        {
          // Set Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4) == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w / 2, destRect.y, DIR_DOWN));

          // Movement
          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          // Offscreen
          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case LEVEL_WATER:
        {
          // Set Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4) == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y, DIR_DOWN));

          // Rockets
          if (ticks % (TARGET_FPS * 8) == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w, destRect.y, DIR_DOWN));

          // Movement
          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          // Offscreen
          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case LEVEL_ICE:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % TARGET_FPS * 4 == 0)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w / 2, destRect.y, DIR_DOWN));

          if (ticks % TARGET_FPS * 5 == 0)
          {
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w, destRect.y + destRect.h / 2, DIR_RIGHT));
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y + destRect.h / 2, DIR_LEFT));
          }

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case LEVEL_SPACE:
        {
          // Movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Rockets
          if (ticks % (TARGET_FPS * 4) < 16)
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + (ticks % (TARGET_FPS * 4)) * 32, destRect.y, DIR_DOWN));

          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
        case LEVEL_VOLCANO:
        {
          // Set movement
          if (ticks % (TARGET_FPS * 3) == 0)
            dir = rand() % 2;

          // Down Rockets
          if (ticks % (TARGET_FPS * 4 )== 0)
          {
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y, DIR_DOWN));
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x + destRect.w, destRect.y, DIR_DOWN));
          }

          // Side rockets
          if (ticks % TARGET_FPS * 5 == 0)
          {
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y + destRect.h / 2, DIR_RIGHT));
            objects.push_back(new Rocket(GameItem::renderer, player, destRect.x, destRect.y + destRect.h / 2, DIR_LEFT));
          }

          // Movement
          if (dir)
            destRect.x += 4;
          else
            destRect.x -= 4;

          // Flip direction if offscreen
          if (destRect.x < 0 || destRect.x + destRect.w > WINDOW_WIDTH)
            dir = !dir;

          break;
        }
      }

      // If the boss is defeated change the game state to WIN
      if (health <= 0)
      {
        Game::levelInfo.bossDefeated = true;
        Game::levelInfo.cutScene = true;
      }

      // Update all projectiles
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
        // Move to correct position if not there
        if (destRect.y != Game::camera.y + 48)
          destRect.y += ((Game::camera.y + 16) - destRect.y) / 8;

        if (Game::levelInfo.bossDefeated)
          removeObjects();
      }
    }

    // Animations
    switch (Game::levelInfo.level)
    {
      case LEVEL_GRASS:
      {
        if (ticks % (TARGET_FPS / 4) == 0)
        {
          if (animationState < 3)
            animationState++;
          else
            animationState = 0;
        }

        switch (animationState)
        {
          case 0:
            srcRect.y = 0;
            break;
          case 1:
            srcRect.y = 16;
            break;
          case 2:
            srcRect.y = 32;
            break;
          case 3:
            srcRect.y = 16;
            break;
        }

        break;
      }
      case LEVEL_WATER:
      {
        break;
      }
      case LEVEL_ICE:
      {
        if (ticks % (TARGET_FPS / 4) == 0)
        {
          if (animationState < 3)
            animationState++;
          else
            animationState = 0;
        }

        switch (animationState)
        {
          case 0:
            srcRect.y = 0;
            break;
          case 1:
            srcRect.y = 16;
            break;
          case 2:
            srcRect.y = 32;
            break;
          case 3:
            srcRect.y = 16;
            break;
        }

        break;
      }
      case LEVEL_SPACE:
      {
        break;
      }
      case LEVEL_VOLCANO:
      {
        if (ticks % (TARGET_FPS / 4) == 0)
        {
          if (animationState < 1)
            animationState++;
          else
            animationState = 0;
        }

        switch (animationState)
        {
          case 0:
            srcRect.y = 0;
            break;
          case 1:
            srcRect.y = 16;
            break;
        }

        break;
      }
      case LEVEL_CASTLE:
      {
        break;
      }
    }
  }
}

void Boss::draw()
{
  SDL_Rect dRect = {destRect.x, destRect.y - Game::camera.y, destRect.w, destRect.h};
  GameItem::renderer->copy(texture, &srcRect, &dRect);

  // Draw health
  if (!Game::levelInfo.bossDefeated)
  {
    SDL_Rect healthBar = {WINDOW_WIDTH - (WINDOW_WIDTH / 2) - 16, 16, (int) ((WINDOW_WIDTH / 2) * (health / 20.0)), 16};
    if (health > 10)
      GameItem::renderer->setDrawColor(0x3e, 0x89, 0x48, 255);
    else if (health > 5)
      GameItem::renderer->setDrawColor(0xfe, 0xea, 0x34, 255);
    else
      GameItem::renderer->setDrawColor(0xe4, 0x3b, 0x44, 255);
    GameItem::renderer->fillRect(&healthBar);
  }

  ItemManager::draw();
}
