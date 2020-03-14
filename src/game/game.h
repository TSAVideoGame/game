#ifndef GAME
#define GAME

#include "window.h"
#include "renderer.h"
#include "texture.h"
#include "manager_manager.h"
#include "game_input.h"
#include "mixer.h"

class GameStates;

struct Camera
{
  int x;
  int y;
};

struct LevelInfo
{
  int level;
  int maxHeight;
  int difficulty;
  int maxDifficulty;
  bool cutScene;
  bool cutSceneOver;
  int time;
  bool paused;
  bool bossDefeated;
};

class Game
{
public:
  static void init(const char* title, int x, int y, int width, int height, bool fullScreen);
  static void close();

  static void input();
  static void update();
  static void draw();

  static bool isRunning();
  static Texture* getTexture();
  static GameInput inputs;
  static Camera camera;
  static LevelInfo levelInfo;
  static GameStates gameState;
  static Mixer* mixer;
  //consolidate these variables
  static int levelsUnlocked[6];
  static int scores[6];
  static int times[6]; // Time it takes to beat level in ticks
private:
  Game();
  ~Game();

  void updateState();

  static bool running;
  static Window* window;
  static Renderer* renderer;
  static Texture* texture;
  static ManagerManager* manager;
};

#include "game_states.h"

#endif
