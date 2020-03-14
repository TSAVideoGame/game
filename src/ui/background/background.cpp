#include "background.h"
#include "constants.h"
#include "game.h"
#include <cmath>
#include <SDL2/SDL.h>

Background::Background(Renderer* ren, const char* imagePath) : GameItem(ren)
{
  texture = new Texture(imagePath, ren);
  ticks = 0;
}

Background::Background(Renderer* ren, const char* imagePath, int w, Player* p) : GameItem(ren)
{
  texture = new Texture(imagePath, ren);
  width = w;
  player = p;
  ticks = 0;
}

Background::~Background()
{
  delete texture;
}

void Background::update()
{
  // The % of excess width offscreen is equal to the player's % of the window's width
  if (Game::gameState.getState() == GameState::LEVEL && player)
  {
    ticks++;
    destRect = {(int) (-1 * ((float) player->getDelta().x / WINDOW_WIDTH) * (width - WINDOW_WIDTH)), 0, width, 800};
  }
  else
  {
    destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  }

}

void Background::draw()
{
  SDL_Rect dRect = {destRect.x, destRect.y, destRect.w, destRect.h};
  // dRect.x > 0 ? dRect.x = 0 : dRect.x = dRect.x;
  renderer->copy(texture, NULL, &dRect);
}

void Background::setXY(int x, int y)
{
  destRect.x = x;
  destRect.y = y;
}
