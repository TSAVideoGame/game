#include "number.h"
#include "renderer.h"
#include "game_states.h"
#include "game.h"
#include <cmath>

#include <iostream>

Number::Number(Renderer* ren, int* s, int x, int y, int w, int pos) : GameItem(ren)
{
  score = s;
  width = w;
  destRect = {x, y, width, width * 18 / 16};
  position = pos;
}

Number::~Number()
{

}

void Number::update()
{
  setSrc();
}

void Number::setSrc()
{
  int a = *score;
  int digits = 0;
  while (a != 0)
  {
    a /= 10;
    digits++;
  }
  if (digits == 0)
    digits = 1;
  int place = 0;
  place = (int) (log10(pow(pow(10, digits - 1), 1.0 / position)) + 1);
  int digit = (int) (*score / pow(10, place - 1)) % 10;
  srcRect = {16 * (digit % 4), 423 + 18 * (digit / 4), 16, 18};
}

void Number::goTo(int x, int y)
{
  destRect.x += (x - destRect.x) / 4;
  destRect.y += (y - destRect.y) / 4;
}
