#include "renderer.h"
#include "texture.h"

Renderer::Renderer(SDL_Window* window)
{
  renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  setDrawColor(0xff, 0xff, 0xff, 255);
  clear();
  present();
}

Renderer::~Renderer()
{
  SDL_DestroyRenderer(renderer);
}

void Renderer::present()
{
  SDL_RenderPresent(renderer);
}

void Renderer::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Renderer::clear()
{
  SDL_RenderClear(renderer);
}

void Renderer::fillRect(SDL_Rect* destRect)
{
  SDL_RenderFillRect(renderer, destRect);
}

void Renderer::copy(Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect)
{
  SDL_RenderCopy(renderer, texture->getTexture(), srcRect, destRect);
}

void Renderer::copy(Texture* texture, SDL_Rect* srcRect, SDL_Rect* destRect, double angle)
{
  SDL_RenderCopyEx(renderer, texture->getTexture(), srcRect, destRect, angle, NULL, SDL_FLIP_NONE);
}

SDL_Renderer* Renderer::getRenderer()
{
  return renderer;
}

void Renderer::setAlpha(Texture* texture, Uint8 a)
{
  SDL_SetTextureAlphaMod(texture->getTexture(), a);
}
