#include "tutorial.h"
#include "game.h"

Tutorial::Tutorial(Renderer* ren, Texture* text, SDL_Rect sRect, SDL_Rect dRect) : GameItem(ren)
{
  texture = text;
  srcRect = sRect;
  destRect = dRect;
}

Tutorial::~Tutorial()
{

}

void Tutorial::update()
{

}

void Tutorial::draw()
{
  SDL_Rect dRect = destRect;
  dRect.y -= Game::camera.y;
  renderer->setAlpha(texture, 204);
  renderer->copy(texture, &srcRect, &dRect);
  renderer->setAlpha(texture, 255);
}
