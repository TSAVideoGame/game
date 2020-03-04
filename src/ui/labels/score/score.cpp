#include "score.h"
#include "number.h"

Score::Score(Renderer* ren, int* s, int x, int y, int w) : GameItem(ren), ItemManager(ren)
{
  score = s;
  myPos = {x, y, w, 0};
}

Score::~Score()
{

}

void Score::update()
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
  while (objects.size() < digits)
  {
    objects.push_back(new Number(ItemManager::renderer, score, (myPos.w * (objects.size() + 1)) + myPos.x, myPos.y, myPos.w, (objects.size() + 1)));
  }

  for (int i = 0; i < objects.size(); i ++)
    dynamic_cast<Number*>(objects[i])->goTo(myPos.x + myPos.w * i, myPos.y);

  ItemManager::update();
}

void Score::draw()
{
  //GameItem::draw();
  ItemManager::draw();
}

void Score::goTo(int x, int y)
{
  myPos.x += (x - myPos.x) / 4;
  myPos.y += (y - myPos.y) / 4;
}
