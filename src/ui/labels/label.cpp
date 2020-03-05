#include "label.h"

Label::Label(Renderer* ren, SDL_Rect sRect, SDL_Rect dRect) : GameItem(ren)
{
  srcRect = sRect;
  destRect = dRect;
}

Label::~Label()
{

}

void Label::update()
{

}

void Label::goTo(int x, int y)
{
  destRect.x += (x - destRect.x) / 4;;
  destRect.y += (y - destRect.y) / 4;
}

void Label::setSrc(SDL_Rect sRect)
{
  srcRect = sRect;
}
