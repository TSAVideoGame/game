#include "button.h"
#include <SDL2/SDL.h>
#include <cmath>
#include "game.h"

Button::Button(Renderer* renderer, SDL_Rect srcRect, SDL_Rect myPos, void (*clickHandler)(Button*)) : UIComponent(renderer)
{
  this->srcRect = srcRect;
  this->myPos = myPos;
  destRect = myPos;
  onClick = clickHandler;
  state = ButtonState::NEUTRAL;
}

void Button::update()
{
  switch (state)
  {
    case ButtonState::NEUTRAL:
    {
      ticks = 0;
      if (focused())
      {
        state = ButtonState::HOVER;
      }
      break;
    }
    case ButtonState::HOVER:
    {
      ticks++;
      int range = 4;
      double compression = 0.25;
      destRect.y = myPos.y + (std::sin(compression * ticks) * range);

      if (Game::inputs.attack)
      {
        onClick(this);
      }
      if (!focused())
      {
        destRect = myPos;
        state = ButtonState::NEUTRAL;
      }
    }
  }
}

bool Button::focused()
{
  return (Game::inputs.mouseX >= myPos.x &&
          Game::inputs.mouseX <= myPos.x + destRect.w &&
          Game::inputs.mouseY >= myPos.y &&
          Game::inputs.mouseY <= myPos.y + destRect.h);
}

void Button::click()
{
  onClick(this);
}

void Button::goTo(int x, int y)
{
  myPos.x += (x - myPos.x) / 4;
  myPos.y += (y - myPos.y) / 4;
  destRect = myPos;
}
