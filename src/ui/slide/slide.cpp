#include "slide.h"

Slide::Slide(Renderer* ren, const char* imagePath) : GameItem(ren)
{
  texture = new Texture(imagePath, ren);
}

Slide::~Slide()
{
  delete texture;
}

void Slide::update()
{

}

void Slide::draw()
{
  renderer->copy(texture, NULL, NULL);
}
