#include "button_manager.h"
#include "button.h"
#include "game.h"
#include "game_states.h"
#include "constants.h"

#include <SDL2/SDL.h>

static int buttonW = 128;
static int buttonH = 64;

static void quit(Button* button)
{
  Game::gameState.changeState(GameState::QUIT);
}

static void menu(Button* button)
{
  Game::gameState.changeState(GameState::MENU);
}

static void startLevel(Button* button)
{
  if (Game::levelsUnlocked[Game::levelInfo.level])
    Game::gameState.changeState(GameState::LEVEL);
}

static void pauseLevel(Button* button)
{
  Game::levelInfo.paused = !Game::levelInfo.paused;
}

ButtonManager::ButtonManager(Renderer* ren) : ItemManager(ren)
{

}

ButtonManager::~ButtonManager()
{

}

void ButtonManager::update()
{
  // Handle object creation and deletion
  if (Game::gameState.getFirstTick())
  {
    removeObjects();
    switch (Game::gameState.getState())
    {
      case GameState::HOME:
      {
        Button* button;
        button = new Button(renderer, {0, 0, 64, 32}, {(WINDOW_WIDTH / 2) - (buttonW / 2), (WINDOW_HEIGHT / 2) - (buttonH / 2), buttonW, buttonH}, menu);
        objects.push_back(button);
        button = new Button(renderer, {64, 0, 64, 32}, {(WINDOW_WIDTH / 2) - (buttonW / 2), (WINDOW_HEIGHT / 2) - (buttonH / 2) + buttonH * 2, buttonW, buttonH}, quit);
        objects.push_back(button);
        break;
      }
      case GameState::MENU:
      {
        for (int i = 0; i < 6; i++)
        {
          objects.push_back(new Button(renderer, {0, 0, 64, 32}, {(WINDOW_WIDTH / 2 - 64) + (i * 512) - (Game::levelInfo.level * 512), WINDOW_HEIGHT + 8, buttonW, buttonH}, startLevel));
        }
        break;
      }
      case GameState::LEVEL:
      {
        Game::levelInfo.paused = false;
        objects.push_back(new Button(renderer, {416, 128, 32, 32}, {WINDOW_WIDTH - 48, 16, 32, 32}, pauseLevel));
        break;
      }
      case GameState::OVER:
      {
        Button* button;
        button = new Button(renderer, {128, 0, 64, 32}, {WINDOW_WIDTH / 2 - (buttonW / 2), (WINDOW_HEIGHT) - buttonH * 3, buttonW, buttonH}, menu);
        objects.push_back(button);
        break;
      }
      case GameState::WIN:
      {
        Button* button;
        button = new Button(renderer, {128, 0, 64, 32}, {WINDOW_WIDTH / 2 - (buttonW / 2), (WINDOW_HEIGHT) - buttonH * 3, buttonW, buttonH}, menu);
        objects.push_back(button);
        break;
      }
    }
  }

  if (Game::gameState.getState() == GameState::MENU)
  {
    for (int i = 0; i < objects.size(); i++)
    {
      if (i == Game::levelInfo.level)
      {
        dynamic_cast<Button*>(objects[i])->goTo((WINDOW_WIDTH / 2 - 64) + (i * 512) - (Game::levelInfo.level * 512), (WINDOW_HEIGHT) - buttonH *  3);
        if (Game::levelsUnlocked[i])
          dynamic_cast<Button*>(objects[i])->setSrc({0, 0, 64, 32});
        else
          dynamic_cast<Button*>(objects[i])->setSrc({64, 0, 64, 32});
      }
      else
        dynamic_cast<Button*>(objects[i])->goTo((WINDOW_WIDTH / 2 - 64) + (i * 512) - (Game::levelInfo.level * 512), WINDOW_HEIGHT + 8);
    }
  }
  else if (Game::gameState.getState() == GameState::LEVEL)
  {
    if (Game::levelInfo.paused)
    {
      if (objects.size() < 2)
        objects.push_back(new Button(renderer, {64, 0, 64, 32}, {(WINDOW_WIDTH / 2) - (buttonW / 2), (WINDOW_HEIGHT / 2) - (buttonH / 2) + buttonH * 2, buttonW, buttonH}, menu));
    }
    else
    {
      if (objects.size() > 1)
        objects.pop_back();
    }
  }

  Manager::update(); // Call the update of every object
}
