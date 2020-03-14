#include "dialog.h"
#include "renderer.h"
#include "texture.h"

static int dialogW = 1200;
static int dialogH = 200;

Dialog::Dialog(Renderer* ren, Texture* texture, int srcX, int srcY, int destY) : GameItem(ren)
{
  srcRect = {srcX, srcY, dialogW, dialogH};
  destRect = {0, destY, dialogW, dialogH};
  myTexture = texture;
  renderer->setAlpha(myTexture, 192);
}

Dialog::~Dialog()
{

}

void Dialog::update()
{

}

void Dialog::draw()
{
  renderer->copy(myTexture, &srcRect, &destRect);
}
