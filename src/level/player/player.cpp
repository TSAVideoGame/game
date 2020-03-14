#include "player.h"
#include "constants.h"
#include "game_states.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <deque>

Player::Player(Renderer* ren) : GameItem(ren)
{
  reset();
}

Player::~Player()
{

}

void Player::update()
{
  if (Game::gameState.getState() == GameState::LEVEL && !Game::levelInfo.cutScene && !Game::levelInfo.paused)
  {
    ticks++;

    delta = destRect;
    deltas.pop_back();
    deltas.push_front(delta);

    // Check if can jump
    if (Game::inputs.up)
    {
      if (maxYVel < defMaxMaxYVel && canJump && ticks % 2 == 0)
      {
        maxYVel += 1;
      }

      if (canJump)
      {
        trampTicks++;
      }

      shouldJump = true;
    }
    else
    {
      trampTicks = 1;
      if (shouldJump && canJump)
      {
        jumping = true;
        canJump = false;
        Game::mixer->playSfx(SFX_JUMP);
      }
      shouldJump = false;
    }

    // Flip
    if (Game::inputs.special && canFlip && airTicks > 1 && flipTicks == 0)
    {
      flipping = true;
      canFlip = false;
      flipTicks = 0;
      boosting = false;
      boostTicks = 0;
    }

    if (flipping == true)
    {
      flipTicks++;
      if (flipTicks < TARGET_FPS / 2)
        yVel -= .25;
      if (flipTicks > TARGET_FPS - 1)
        flipping = false;
    }
    else
    {
      if (flipTicks < TARGET_FPS && flipTicks != 0)
        flipTicks++;
      else
        flipTicks = 0;
    }

    // Check if can boost
    if (Game::inputs.attack && canBoost && (Game::inputs.left || Game::inputs.right) && airTicks > 1)
    {
      flipping = false;
      flipTicks = 0;
      boosting = true;
      if (Game::inputs.left)
        boostDir = 2;
      else if (Game::inputs.right)
        boostDir = 3;
      else
        boosting = false;
      canBoost = false;
    }

    if (boosting)
    {
      boostTicks++;
      if (boostTicks > 8)
      {
        boosting = false;
        yVel = -10;
        xVel = 0;
      }
      switch (boostDir)
      {
        case 2:
          destRect.x -= boostTicks * 2;
          break;
        case 3:
          destRect.x += boostTicks * 2;
      }
    }
    else // Not Boosting
    {
      if (Game::inputs.left || Game::inputs.right)
      {
        sideTicks++;
        if (sideTicks > TARGET_FPS / 4)
          sideTicks = -TARGET_FPS / 4;
        if (Game::inputs.left)
        {
          if (-xVel < maxXVel)
            xVel -= 0.5;
        }
        else
        {
          if (xVel < maxXVel)
            xVel += 0.5 ;
        }
      }
      else
      {
        // Slide more if the level is ice
        if (Game::levelInfo.level == LEVEL_ICE)
          ;
        else
          xVel /= 2;
        sideTicks = 0;
      }

      if (!jumping)
      {
        yVel += 0.5;

        if ((Game::levelInfo.level == LEVEL_WATER || Game::levelInfo.level == LEVEL_SPACE) && yVel > 5)
          yVel = 5;

        if (Game::inputs.up)
        {
          if (yVel < 0)
            yVel += 1;
          else
            yVel *= 1.1;
        }
      }
      else
      {
        /*if (Game::levelInfo.level == 3)
        {
          if (-yVel < maxYVel / 2)
            yVel--;
          else
          {
            maxYVel = defMinMaxYVel;
            jumping = false;
          }
        }
        else*/
        {
          yVel = -maxYVel;
          maxYVel = defMinMaxYVel;
          jumping = false;
        }
      }

      destRect.y += yVel;
      destRect.x += xVel;

      if (yVel > 0)
      {
        // Player is going down
        if (destRect.y + destRect.h / 2 >= Game::camera.y + WINDOW_HEIGHT - WINDOW_HEIGHT / 4)
          Game::camera.y = (destRect.y + destRect.h / 2) - WINDOW_HEIGHT + WINDOW_HEIGHT / 4;

        if (Game::levelInfo.cutSceneOver && Game::camera.y > Game::levelInfo.maxHeight - WINDOW_HEIGHT + 16)
          Game::camera.y = Game::levelInfo.maxHeight - WINDOW_HEIGHT + 16;
      }
      else
      {
        // Player is going up
        if (destRect.y + destRect.h / 2 <= Game::camera.y + WINDOW_HEIGHT / 4)
        {
          Game::camera.y = (destRect.y + destRect.h / 2) - WINDOW_HEIGHT / 4;
          if (Game::camera.y < Game::levelInfo.maxHeight && Game::levelInfo.difficulty != Game::levelInfo.maxDifficulty)
            Game::levelInfo.maxHeight = Game::camera.y;
        }
      }
    }
    airTicks++;
    if (airTicks > 2)
      canJump = false;

    if (destRect.x < 0)
    {
      destRect.x = 0;
      xVel /= -2;
    }

    if (destRect.x + destRect.w > WINDOW_WIDTH)
    {
      destRect.x = WINDOW_WIDTH - destRect.w;
      xVel /= -2;
    }

    if (destRect.y > WINDOW_HEIGHT)
      Game::gameState.changeState(GameState::OVER);

    if (destRect.y < Game::levelInfo.maxHeight && canJump && !Game::levelInfo.cutSceneOver)
      Game::levelInfo.cutScene = true;
  }

  if (Game::levelInfo.cutScene)
  {
    yVel++;
    destRect.y += yVel;
  }
}

void Player::draw()
{
  // Trail effect if boosting
  if (boosting)
  {
    for (auto pos : deltas)
    {

      SDL_Rect dRect = {pos.x, (pos.y + maxYVel / 5) - Game::camera.y, pos.w, pos.h};
      renderer->setAlpha(Game::getTexture(), 64);
      renderer->copy(Game::getTexture(), &srcRect, &dRect);
      renderer->setAlpha(Game::getTexture(), 255);
    }
  }

  // Get src
  if (trampTicks % (-maxYVel / 5 + 20) == 0)
    srcRect = {128, 32, 64, 64};
  else
    if (sideTicks > 0)
      srcRect = {64, 32, 64, 64};
    else
      srcRect = {0, 32, 64, 64};
  SDL_Rect dRect = {destRect.x, (destRect.y + maxYVel / 5) - Game::camera.y, destRect.w, destRect.h};

  // Roate if flipping
  if (flipTicks > 0)
  {
    renderer->copy(Game::getTexture(), &srcRect, &dRect, 360 / TARGET_FPS * flipTicks);
  }
  else
    renderer->copy(Game::getTexture(), &srcRect, &dRect);

  // Draw health
  SDL_Rect healthBar = {16, 32, (int) ((WINDOW_WIDTH / 4) * (health / 20.0)), 16};
  if (health > 15)
    renderer->setDrawColor(0x3e, 0x89, 0x48, 255);
  else if (health > 5)
    renderer->setDrawColor(0xfe, 0xea, 0x34, 255);
  else
    renderer->setDrawColor(0xe4, 0x3b, 0x44, 255);
  renderer->fillRect(&healthBar);
}

SDL_Rect Player::getPos()
{
  return destRect;
}

SDL_Rect Player::getDelta()
{
  return delta;
}

void Player::setPos(int x, int y)
{
  destRect.x = x;
  destRect.y = y;
  if (Game::inputs.up)
    yVel = 0;
  else
    if (yVel > 5)
      yVel = -yVel / 2;
    else
      yVel = 0;

  canJump = true;
  airTicks = 0;

  canBoost = true;
  boostTicks = 0;
  boosting = false;

  canFlip = true;
  flipping = false;
}

void Player::hit(int dir, int change, EnemyTypes enemyT)
{
  Game::mixer->playSfx(SFX_HIT);
  switch (enemyT)
  {
    case EnemyTypes::enemy:
    {
      switch (dir)
      {
        // Player hit top, jump
        case DIR_UP:
          destRect.y += change - 8;
          jumping = true;

          boostTicks = 0;
          canBoost = true;

          canFlip = true;

          yVel = 0;
          maxYVel = 20;
          break;
        // Player hit bottom, fall
        case DIR_DOWN:
          if (!boosting)
          {
            jumping = false;
            yVel = 0;
            destRect.y -= change;
            health--;
          }
          break;
        // Player hit left
        case DIR_LEFT:
          destRect.x -= change;
          xVel = -10;
          if (boosting)
          {
            boostTicks = 0;
            boosting = false;
            jumping = true;
            canBoost = true;
            canFlip = true;
            yVel = 0;
            maxYVel = 20;
          }
          else
          {
            jumping = false;
            health--;
          }
          break;
        // Player hit right
        case DIR_RIGHT:
          destRect.x += change;
          xVel = 10;
          if (boosting)
          {
            boostTicks = 0;
            boosting = false;
            jumping = true;
            canBoost = true;
            canFlip = true;
            yVel = 0;
            maxYVel = 20;
          }
          else
          {
            jumping = false;
            health--;
          }
          break;
      }
      break;
    }
    case EnemyTypes::boss:
    {
      switch (dir)
      {
        // Player hit top
        case DIR_UP:
          destRect.y += change - 8;
          jumping = true;

          boostTicks = 0;
          canBoost = true;

          canFlip = true;

          yVel = 0;
          maxYVel = 20;
          break;
        // Player hit bottom
        case DIR_DOWN:
          if (!boosting)
          {
            jumping = false;
            yVel = 0;
            destRect.y -= change;
            health--;
          }
          break;
        // Player hit left
        case DIR_LEFT:
          destRect.x -= change;
          xVel = -20;
          if (boosting)
          {
            boostTicks = 0;
            boosting = false;
            canFlip = true;
            jumping = true;
            canBoost = true;
            yVel = 0;
            maxYVel = defMinMaxYVel;
          }
          else
          {
            jumping = false;
            health--;
          }
          break;
        // Player hit right
        case DIR_RIGHT:
          destRect.x += change;
          xVel = 20;
          if (boosting)
          {
            boostTicks = 0;
            boosting = false;
            canFlip = true;
            jumping = true;
            canBoost = true;
            yVel = 0;
            maxYVel = defMinMaxYVel;
          }
          else
          {
            jumping = false;
            health--;
          }
          break;
      }
      break;
    }
    case EnemyTypes::rocket:
    {
      switch (dir)
      {
        // Player hit top
        case DIR_UP:
          destRect.y += change - 8;
          jumping = true;
          boostTicks = 0;
          canBoost = true;
          yVel = 0;
          maxYVel = 20;
          break;
        // Player hit bottom
        case DIR_DOWN:
          if (!boosting)
          {
            jumping = false;
            yVel = 0;
            destRect.y -= change;
            health--;
          }
          break;
        // Player hit left
        case DIR_LEFT:
          destRect.x -= change;
          xVel = -10;
          if (boosting)
          {
            boostTicks = 0;
            boosting = false;
            jumping = true;
            canBoost = true;
            yVel = 0;
            maxYVel = 20;
          }
          else
          {
            jumping = false;
            health--;
          }
          break;
        // Player hit right
        case DIR_RIGHT:
          destRect.x += change;
          xVel = 10;
          if (boosting)
          {
            boostTicks = 0;
            boosting = false;
            jumping = true;
            canBoost = true;
            yVel = 0;
            maxYVel = 20;
          }
          else
          {
            jumping = false;
            health--;
          }
          break;
      }
      break;
    }
  }

  if (health <= 0)
    Game::gameState.changeState(GameState::OVER);
}

int Player::getMaxYVel()
{
  return maxYVel;
}

void Player::reset()
{
  destRect = {WINDOW_WIDTH / 2 - 32, WINDOW_HEIGHT - 64 * 6, 64, 64};
  srcRect = {0, 32, 64, 64};
  delta = destRect;
  deltas.clear();
  for (int i = 0; i < 10; i++)
    deltas.push_back(delta);

  canJump = false;
  jumping = false;
  shouldJump = false;

  boosting = false;
  canBoost = true;
  boostTicks = 0;

  flipping = false;
  canFlip = true;
  flipTicks = 0;

  ticks = 0;
  trampTicks = 0;
  airTicks = 0;
  sideTicks = 0;

  yVel = 0;
  xVel = 0;
  defMinMaxYVel = 5;
  defMaxMaxYVel = 40;
  maxYVel = defMinMaxYVel;
  maxXVel = 10;

  health = 20;
}
