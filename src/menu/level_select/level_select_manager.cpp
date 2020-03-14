#include "level_select_manager.h"
#include "level_tile.h"
#include "game_states.h"
#include "game.h"
#include "constants.h"
#include <fstream>
#include <string>

LevelSelectManager::LevelSelectManager(Renderer* ren) : ItemManager(ren)
{
  // If a save exists load the save
  std::fstream save;
  save.open("res/save/1.sav");
  if (save)
  {
    // Load Unlocked Levels
    for (int i = 0; i < 7; i++)
    {
      char c = save.get();
      if (c != '\n')
        Game::levelsUnlocked[i] = c - '0';
    }

    // Load Scores and Times
    std::string score;
    std::string time;
    bool passedComma = false;
    int i = 0;
    while (!save.eof())
    {
      char c = save.get();
      if (c == '\n')
      {
        Game::scores[i] = std::stoi(score);
        Game::times[i] = std::stoi(time);
        score = "";
        time = "";
        passedComma = false;
        i++;
      }
      else if (passedComma)
      {
        time += c;
      }
      else
      {
        if (c == ',')
          passedComma = true;
        else
          score += c;
      }
    }
  }
  else
  {
    saveGame();
  }
  save.close();
}

LevelSelectManager::~LevelSelectManager()
{

}

void LevelSelectManager::update()
{
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    switch (Game::gameState.getState())
    {
      case GameState::MENU:
      {
        saveGame();
        LevelTile* l;
        l = new LevelTile(renderer, "res/images/menu/level_tiles/level_1.png", true);
        objects.push_back(l);
        l = new LevelTile(renderer, "res/images/menu/level_tiles/level_2.png", false);
        objects.push_back(l);
        l = new LevelTile(renderer, "res/images/menu/level_tiles/level_3.png", false);
        objects.push_back(l);
        l = new LevelTile(renderer, "res/images/menu/level_tiles/level_4.png", false);
        objects.push_back(l);
        l = new LevelTile(renderer, "res/images/menu/level_tiles/level_5.png", false);
        objects.push_back(l);
        l = new LevelTile(renderer, "res/images/menu/level_tiles/level_1.png", false);
        objects.push_back(l);
      }
    }
  }

  switch (Game::gameState.getState())
  {
    case GameState::MENU:
    {
      for (int i = 0; i < objects.size(); i++)
      {
        if (dynamic_cast<LevelTile*>(objects[i])->focused())
        {
          if (Game::inputs.attack)
          {
            Game::levelInfo.level = i;
            switchSelected(dynamic_cast<LevelTile*>(objects[i]));
          }
        }

        int arb = 512;
        dynamic_cast<LevelTile*>(objects[i])->setXY((WINDOW_WIDTH / 2 - 192) + (i * arb) - (Game::levelInfo.level * arb), WINDOW_HEIGHT / 2 - 192);
      }
    }
  }

  Manager::update();
}

void LevelSelectManager::switchSelected(LevelTile* lT)
{
  for (auto tile : objects)
  {
    if (dynamic_cast<LevelTile*>(tile) == lT)
      dynamic_cast<LevelTile*>(tile)->isSelected = true;
    else
      dynamic_cast<LevelTile*>(tile)->isSelected = false;
  }
}

void LevelSelectManager::saveGame()
{
  std::fstream save;
  save.open("res/save/1.sav", std::fstream::out | std::fstream::trunc);
  // Import level unlocked
  for (int i = 0; i < 6; i++)
    save << Game::levelsUnlocked[i];
  save << '\n';
  // Import level scores and times
  for (int i = 0; i < 6; i++)
    save << Game::scores[i] << "," << Game::times[i] << '\n';
  save.close();
}
