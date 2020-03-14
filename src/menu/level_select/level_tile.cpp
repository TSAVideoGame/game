#include "level_tile.h"

static int hoverDist = 16;

LevelTile::LevelTile(Renderer* ren, const char* filepath, bool selected) : GameItem(ren)
{
  destRect.w = 384;
  destRect.h = 384;
  isSelected = selected;
  texture = new Texture(filepath, ren);
}

LevelTile::~LevelTile()
{
  delete texture;
}

void LevelTile::update()
{
  if (destRect.x != myX)
    destRect.x += (myX - destRect.x) / 4;

  if (focused({myX, myY, destRect.w, destRect.h}))
  {
    if (destRect.y != (myY - hoverDist))
      destRect.y += ((myY - hoverDist) - destRect.y) / 4;
  }
  else
  {
    if (destRect.y != myY)
      destRect.y += (myY - destRect.y) / 4;
  }

}

void LevelTile::draw()
{
  SDL_Rect renderRect = {destRect.x, destRect.y, destRect.w, destRect.h};
  if (isSelected)
    renderRect = {destRect.x - 16, destRect.y - 16, destRect.w + 32, destRect.h + 32};
  renderer->copy(texture, NULL, &renderRect);
}

void LevelTile::setXY(int x, int y)
{
  myX = x;
  myY = y;
  if (destRect.x == 0 || destRect.y == 0)
  {
    destRect.x = myX;
    destRect.y = myY;
  }

}
