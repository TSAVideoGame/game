#include "background_manager.h"
#include "background.h"
#include "game_states.h"
#include "constants.h"
#include "game.h"

BackgroundManager::BackgroundManager(Renderer* ren) : ItemManager(ren)
{
  mix = new Mixer();
  mix->addTrack("res/music/tsa_boss_1_3.wav");
  mix->addTrack("res/music/title.wav");
  mix->addTrack("res/music/mysterious_shores.wav");
  mix->addTrack("res/music/run.wav");
  mix->addTrack("res/music/ice.wav");
  mix->addTrack("res/music/death.wav");
}

BackgroundManager::~BackgroundManager()
{
  delete mix;
}

void BackgroundManager::update()
{
  if (GameStates::getFirstTick())
  {
    removeObjects();
    mix->stop();
    switch (GameStates::getState())
    {
      case GameState::INTRO:
      {
        mix->play(0);
        break;
      }
      case GameState::HOME:
      {
        mix->play(1);
        Background* b = new Background(renderer, "res/images/home.png", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0);
        objects.push_back(b);
        break;
      }
      case GameState::MENU:
      {
        mix->play(2);
        Background* b;
        b = new Background(renderer, "res/images/home.png", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0);
        objects.push_back(b);
        break;
      }
      case GameState::LEVEL:
      {
        switch (Game::levelInfo.level)
        {
          case 4:
            mix->play(0);
            objects.push_back(new Background(renderer, "res/images/levels/volcano.jpeg", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0));
            break;
          case 3:
            mix->play(3);
            objects.push_back(new Background(renderer, "res/images/levels/space.png", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0));
            break;
          case 2:
            mix->play(4);
            objects.push_back(new Background(renderer, "res/images/levels/ice.png", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0));
            break;
          case 1:
            mix->play(3);
            objects.push_back(new Background(renderer, "res/images/levels/water.png", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0));
            break;
          default:
          case 0:
            mix->play(3);
            objects.push_back(new Background(renderer, "res/images/levels/grass.png", {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}, 0));
            break;
        }
        break;
      }
      case GameState::OVER:
      {
        mix->play(5);
      }
    }
  }
}
