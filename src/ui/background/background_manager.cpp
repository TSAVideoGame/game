#include "background_manager.h"
#include "background.h"
#include "game_states.h"
#include "constants.h"
#include "game.h"

BackgroundManager::BackgroundManager(Renderer* ren, PlayerManager* pM) : ItemManager(ren)
{
  playerM = pM;

  mix = new Mixer();
  mix->addTrack("res/music/tsa_boss_1_3.wav"); // Intro
  mix->addTrack("res/music/title.wav"); // Home
  mix->addTrack("res/music/mysterious_shores.wav"); // Menu
  mix->addTrack("res/music/ice.wav"); // Grass
  mix->addTrack("res/music/run.wav"); // Grass Boss
  mix->addTrack("res/music/run.wav"); // Water
  mix->addTrack("res/music/run.wav"); // Water Boss
  mix->addTrack("res/music/snow_capped_mountain.wav"); // Ice
  mix->addTrack("res/music/run.wav"); // Ice Boss
  mix->addTrack("res/music/run.wav"); // Space
  mix->addTrack("res/music/run.wav"); // Space Boss
  mix->addTrack("res/music/volcano.wav"); // Volcano
  mix->addTrack("res/music/run.wav"); // Volcano Boss
  mix->addTrack("res/music/run.wav"); // Castle
  mix->addTrack("res/music/run.wav"); // Castle Boss
  mix->addTrack("res/music/run.wav"); // Win
  mix->addTrack("res/music/hero_lullaby.wav"); // Lose
}

BackgroundManager::~BackgroundManager()
{
  delete mix;
}

void BackgroundManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    mix->stop();
    switch (Game::gameState.getState())
    {
      case GameState::INTRO:
      {
        mix->play(MUSIC_INTRO);
        break;
      }
      case GameState::HOME:
      {
        mix->play(MUSIC_HOME);
        Background* b = new Background(renderer, "res/images/home.png");
        objects.push_back(b);
        break;
      }
      case GameState::MENU:
      {
        mix->play(MUSIC_MENU);
        Background* b;
        b = new Background(renderer, "res/images/home.png");
        objects.push_back(b);
        break;
      }
      case GameState::LEVEL:
      {
        switch (Game::levelInfo.level)
        {
          case LEVEL_VOLCANO:
            mix->play(MUSIC_VOLCANO);
            objects.push_back(new Background(renderer, "res/images/levels/volcano.jpeg", 1200, playerM->getPlayer()));
            break;
          case LEVEL_SPACE:
            mix->play(MUSIC_SPACE);
            objects.push_back(new Background(renderer, "res/images/levels/space.png", 1200, playerM->getPlayer()));
            break;
          case LEVEL_ICE:
            mix->play(MUSIC_ICE);
            objects.push_back(new Background(renderer, "res/images/levels/ice.png", 1200, playerM->getPlayer()));
            break;
          case LEVEL_WATER:
            mix->play(MUSIC_WATER);
            objects.push_back(new Background(renderer, "res/images/levels/water.png", 1200, playerM->getPlayer()));
            break;
          default:
          case LEVEL_GRASS:
            mix->play(MUSIC_GRASS);
            //objects.push_back(new Background(renderer, "res/images/levels/grass.png", 1200, playerM->getPlayer()));
            objects.push_back(new Background(renderer, "res/images/levels/grass/back.png", 1200, playerM->getPlayer()));
            objects.push_back(new Background(renderer, "res/images/levels/grass/middle.png", 1456, playerM->getPlayer()));
            objects.push_back(new Background(renderer, "res/images/levels/grass/front.png", 1712, playerM->getPlayer()));
            break;
        }
        break;
      }
      case GameState::OVER:
      {
        mix->play(MUSIC_LOSE);
        break;
      }
      case GameState::WIN:
      {
        mix->play(MUSIC_WIN);
        break;
      }
    }
  }

  if (Game::gameState.getState() == GameState::LEVEL)
  {
    if (Game::levelInfo.paused)
    {
      mix->setMusicVolume(Mixer::maxVolume / 4);
    }
    else
    {
      mix->setMusicVolume(Mixer::maxVolume);
    }
  }
  else
  {
    mix->setMusicVolume(Mixer::maxVolume);
  }

  ItemManager::update();
}
