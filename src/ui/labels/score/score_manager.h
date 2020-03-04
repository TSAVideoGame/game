#ifndef SCORE_MANAGER
#define SCORE_MANAGER

#include "item_manager.h"
#include "renderer.h"
#include "texture.h"

/*
 * Called 'score' manager but will display
 * Game::time for the level if the GameState is LEVEL,
 * will display Game::score if the GameState is OVER or WIN
 */

class ScoreManager : public ItemManager
{
public:
  ScoreManager(Renderer*);
  ~ScoreManager();
  void update();
};

#endif
