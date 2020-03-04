#ifndef BUTTON
#define BUTTON

#include "ui_component.h"
#include "renderer.h"
#include <SDL2/SDL.h>

enum class ButtonState {ANIMATE, NEUTRAL, HOVER};

class Button : public UIComponent
{
public:
  // Constructor
  Button(Renderer*, SDL_Rect srcRect, SDL_Rect myPos, void (*clickHandler)(Button*));
  void update();

  void click();
  bool selected;
  SDL_Rect getPos() {return myPos;}
  void setSrc(SDL_Rect sRect) {srcRect = sRect;}
  void goTo(int x, int y);
private:
  void (*onClick)(Button*);
  SDL_Rect myPos;
  unsigned int ticks;
  ButtonState state;

  bool focused();
};

#endif
