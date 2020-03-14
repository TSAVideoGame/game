#include "texture.h"
#include <SDL2/SDL_image.h>
#include "renderer.h"

#include <iostream>

Texture::Texture(const char* fileName, Renderer* ren)
{
  SDL_Surface* tempSurface = IMG_Load(fileName);
  texture = SDL_CreateTextureFromSurface(ren->getRenderer(), tempSurface);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_FreeSurface(tempSurface);
}

Texture::~Texture()
{
  SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getTexture()
{
  return texture;
}
