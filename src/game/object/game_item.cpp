#include "game_item.h"
#include "texture.h"
#include "game.h"


GameItem::GameItem(Renderer* ren)
{
  renderer = ren;
  texture = Game::getTexture();
  // Initalize rects in case not initialized
  srcRect = {0, 0, 0, 0};
  destRect = {0, 0, 0, 0};
}

GameItem::~GameItem()
{

}

void GameItem::draw()
{
  SDL_Rect renderRect = {destRect.x, destRect.y, destRect.w, destRect.h};
  renderer->copy(texture, &srcRect, &renderRect);
}

bool GameItem::focused()
{
  return (Game::inputs.mouseX >= destRect.x &&
          Game::inputs.mouseX <= destRect.x + destRect.w &&
          Game::inputs.mouseY >= destRect.y &&
          Game::inputs.mouseY <= destRect.y + destRect.h);
}

bool GameItem::focused(SDL_Rect rect)
{
  return (Game::inputs.mouseX >= rect.x &&
          Game::inputs.mouseX <= rect.x + rect.w &&
          Game::inputs.mouseY >= rect.y &&
          Game::inputs.mouseY <= rect.y + rect.h);
}
