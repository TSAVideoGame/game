#ifndef TEXTURE
#define TEXTURE

#include <SDL2/SDL.h>

class Renderer;

class Texture
{
public:
  Texture(const char*, Renderer*);
  ~Texture();
  SDL_Texture* getTexture();
private:
  SDL_Texture* texture;
};

#endif
