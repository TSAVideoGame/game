#ifndef GAME_STATES
#define GAME_STATES

#include "game.h"

enum class GameState {INTRO, HOME, MENU, LEVEL, OVER, QUIT, WIN};

class GameStates
{
  friend class Game;
public:
  GameStates();

  GameState getState(); // Return current state
  bool getFirstTick();

  void changeState(GameState); // Queue state for change
private:
  void updateState();
  GameState state;
  GameState newState;
  bool firstTick; // First tick of a state
};

#endif
