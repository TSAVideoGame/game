#include "slide_manager.h"
#include "slide.h"
#include "game_states.h"
#include "game.h"
#include "constants.h"
#include "mixer.h"

static int slideTicks = 0;
static int currentSlide = 0;
static bool fadeIn = true;
static int fadeOpacity = 255;

SlideManager::SlideManager(Renderer* ren) : ItemManager(ren)
{

}

SlideManager::~SlideManager()
{

}

void SlideManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    if (Game::gameState.getState() == GameState::INTRO)
    {
      objects.push_back(new Slide(renderer, ""));
      /*objects.push_back(new Slide(renderer, "res/images/intro/whale_1.jpg"));
      objects.push_back(new Slide(renderer, "res/images/intro/sea_1.jpg"));
      objects.push_back(new Slide(renderer, "res/images/intro/sea_1.jpg"));
      objects.push_back(new Slide(renderer, "res/images/intro/sea_1.jpg"));
      objects.push_back(new Slide(renderer, "res/images/intro/sea_1.jpg"));*/
    }
  }

  if (Game::gameState.getState() == GameState::INTRO)
  {
    if (Game::inputs.special)
    {
      Game::gameState.changeState(GameState::HOME);
    }
    if (fadeIn)
    {
      if (fadeOpacity > 0)
        fadeOpacity -= 5;
      else
      {
        slideTicks++;
        if (slideTicks == TARGET_FPS * 3)
            fadeIn = false;
      }
    }
    else
    {
      if (fadeOpacity < 255)
        fadeOpacity += 5;
      else
      {
        if (currentSlide == objects.size() - 1)
          Game::gameState.changeState(GameState::HOME);
        else
        {
          currentSlide++;
          fadeIn = true;
          slideTicks = 0;
        }
      }
    }
  }
}


void SlideManager::draw()
{
  if (Game::gameState.getState() == GameState::INTRO)
  {
    objects[currentSlide]->draw();

    renderer->setDrawColor(0, 0, 0, fadeOpacity);
    renderer->fillRect(NULL);
  }
}
