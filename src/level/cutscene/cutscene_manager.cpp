#include "cutscene_manager.h"
#include "renderer.h"
#include "game_states.h"
#include "game.h"
#include "constants.h"
#include "dialog.h"
#include "game_input.h"
#include "text_engine.h"

static TextEngine* factoryTextEngine(Renderer* ren, const char* text, int y)
{
  TextEngine* te = new TextEngine(ren, text, 192, y);
  te->addFont(0, "res/fonts/Roboto_Mono/RobotoMono-Regular.ttf", 32, {255, 255, 255});
  te->addSpeed(0, 2);
  return te;
}

CutSceneManager::CutSceneManager(Renderer* ren) : ItemManager(ren)
{
  dialogTexture = new Texture("res/images/dialog/dialog.png", renderer);
}

CutSceneManager::~CutSceneManager()
{
  delete dialogTexture;
}

void CutSceneManager::update()
{
  if (Game::gameState.getFirstTick() && Game::gameState.getState() == GameState::LEVEL)
  {
    removeObjects();
    /*
     * Dialogs have to be inserted in reverse order
     * This is because of how vectors work (pop_back())
     */
    switch (Game::levelInfo.level)
    {
      TextEngine* te;
      case LEVEL_GRASS:
      {
        te = factoryTextEngine(renderer, "...", 24);
        te->addSpeed(1, 8);
        objects.push_back(te);
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "I read the manual", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "What? How did you know that?! That's cheating!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        te = factoryTextEngine(renderer, "That's easy, I just have to hit you from underneath or boost into your sides.", WINDOW_HEIGHT - 176);
        te->setMoving(40, true);
        te->setMoving(50, false);
        te->setMoving(70, true);
        te->setMoving(75, false);
        objects.push_back(te);
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "You can't defeat me, you'll never figure out my weakness!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
        break;
      }
      case LEVEL_WATER:
      {
        objects.push_back(factoryTextEngine(renderer, "Mwahahahahahaha!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "Please, I just need my purse.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "For years, we have been hunted, now feel our wrath!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "Wait, who said challenge? I'm looking for my purse.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "You are a fool to come and challenge me. You will suffer!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
        break;
      }
      case LEVEL_ICE:
        objects.push_back(factoryTextEngine(renderer, "Hrrrrr!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "???", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Hrrrrr", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "It sure is cold!", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));
        break;
      case LEVEL_SPACE:
        objects.push_back(factoryTextEngine(renderer, "IT'S MAY I!!!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "Can I have it, please.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Oh, so that's what this key is for.", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "I'm looking for my purse. Apparently I need to get 5 keys to see the person who stole my purse.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Earthling, why are you here?", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "?", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "BLEEP BLOOP BLOP BLIP BLAP", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
        break;
      case LEVEL_VOLCANO:
        objects.push_back(factoryTextEngine(renderer, "Only if you are a worthy opponent.", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Your boss stole my purse. I need the key to see him.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "Why yes I do, but why should I give it to you?", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Anyways, I'm assuming you have one of those keys?", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "That's a good question. I don't really know, how can I?", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Not funny? How are you even standing the heat?", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "...", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "Is it just me or is it hot in here?", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
        break;
      case LEVEL_CASTLE:
        objects.push_back(factoryTextEngine(renderer, "Oh really, what are you gonna do about it?", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "It's not cool to take other people's things.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "Guess you forgot to tell them.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

        objects.push_back(factoryTextEngine(renderer, "How did you get all the keys? I thought I told them not to give them to you!", 24));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

        objects.push_back(factoryTextEngine(renderer, "So you're that boss.", WINDOW_HEIGHT - 176));
        objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));
        break;
    }
  }

  if (Game::gameState.getState() == GameState::LEVEL && Game::levelInfo.cutScene)
  {
    // Move camera up
    int dest = Game::levelInfo.maxHeight - WINDOW_HEIGHT + 16;
    if (Game::camera.y != dest)
      Game::camera.y += (dest - Game::camera.y) / 8 > -1 ? -1 : (dest - Game::camera.y) / 8;
    else if (objects.size() > 0)
    {
      // If there are dialogues, go to the next dialogue after a right click
      if (Game::inputs.attack)
      {
        if (dynamic_cast<TextEngine*>(objects[objects.size() - 2])->finished())
        {
          objects.pop_back();
          objects.pop_back();
        }
        else
        {
          // Figure out how to skip dialog
        }
      }

    }
    else
    {
      if (!Game::levelInfo.bossDefeated)
      {
        // All the dialogues are over, resume the game
        Game::levelInfo.cutSceneOver = true;
        Game::levelInfo.cutScene = false;
        // Add the boss defeated dialogs
        switch (Game::levelInfo.level)
        {
          TextEngine* te;
          case LEVEL_GRASS:
          {
            objects.push_back(factoryTextEngine(renderer, "Thanks, I guess...", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            te = factoryTextEngine(renderer, "That bag? Our boss has it, and you need 5 keys if you want to get to him. Since you beat me I guess I will give you mine...", 24);
            te->addFont(41, "res/fonts/Roboto_Mono/RobotoMono-Regular.ttf", 32, {0, 255, 0});
            te->setMoving(40, true);
            te->setMoving(45, false);
            te->addFont(45, "res/fonts/Roboto_Mono/RobotoMono-Regular.ttf", 32, {255, 255, 255});
            objects.push_back(te);
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "Where's my purse?", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "Okay, stop! You beat me, what do you want?", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            break;
          }
          case LEVEL_WATER:
          {
            objects.push_back(factoryTextEngine(renderer, "Why yes I do, I guess I'll just give it to you.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "Do you at least have a key? I need it to get back my purse.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "Your overconfidence will be your undoing.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "I'm more than that.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "Impossible! you are just a mere mortal.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
            break;
          }
          case LEVEL_ICE:
          {
            objects.push_back(factoryTextEngine(renderer, "I can't understand you but thanks for the key.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "Hrrrrr", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
            break;
          }
          case LEVEL_SPACE:
          {
            objects.push_back(factoryTextEngine(renderer, "Sure, I don't see why I need it.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "That's fair, but can I have that key?", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "But you need to learn proper English.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "You don't have to get so worked up over a picky word mistake.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));
            break;
          }
          case LEVEL_VOLCANO:
          {
            objects.push_back(factoryTextEngine(renderer, "You don't seem like a bad guy, thanks for the key.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "Did I put them there? Must've forgotten.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "Why are there even trampolines in a volcano?", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "You're pretty food at that trampoline thing.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
            break;
          }
          case LEVEL_CASTLE:
          {
            objects.push_back(factoryTextEngine(renderer, "Sure", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "Really, so we can be friends?", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "You've caused me a lot of trouble, but you've changed so I'm not mad anymore.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "You have humbled me, I thank you.", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));

            objects.push_back(factoryTextEngine(renderer, "That doesn't matter if you do petty things like taking other people's stuff.", WINDOW_HEIGHT - 176));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, WINDOW_HEIGHT - 200));

            objects.push_back(factoryTextEngine(renderer, "How did you defeat me? I thought I was the best. I thought I was unbeatable!", 24));
            objects.push_back(new Dialog(renderer, dialogTexture, 0, 0, 0));
            break;
          }
        }
      }
      else
      {
        Game::gameState.changeState(GameState::WIN);
      }
    }
  }

  // Only update last two items
  if (Game::gameState.getState() == GameState::LEVEL && Game::levelInfo.cutScene && objects.size() > 0)
  {
    // objects[objects.size() - 1]->update(); Dialog doesn't update
    objects[objects.size() - 2]->update();
  }
}

void CutSceneManager::draw()
{
  // Only draw the last dialogue
  if (Game::gameState.getState() == GameState::LEVEL && Game::levelInfo.cutScene && objects.size() > 0)
  {
    objects[objects.size() - 1]->draw();
    objects[objects.size() - 2]->draw();
  }
}
