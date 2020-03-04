#ifndef NUMBER
#define NUMBER

#include "game_item.h"
#include "renderer.h"
#include "texture.h"

class Number : public GameItem
{
public:
  Number(Renderer*, int* score, int x, int y, int w, int pos);
  ~Number();
  void update();
  void goTo(int x, int y);
private:
  int* score;
  int width;
  void setSrc();
  int position;
};

#endif
