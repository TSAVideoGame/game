#include "game.h"
#include "game_states.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

GameInput Game::inputs = {false, false, false, false, false, false, 0, 0};
bool Game::running = true;
Window* Game::window;
Renderer* Game::renderer;
Texture* Game::texture;
ManagerManager* Game::manager;
Camera Game::camera = {0, 0};
GameStates Game::gameState = GameStates();
Mixer* Game::mixer;
LevelInfo Game::levelInfo = {0, 0, 0, 5, false, false, false, false};
int Game::levelsUnlocked[6] = {1, 0, 0, 0, 0, 0};
int Game::scores[6] = {0, 0, 0, 0, 0, 0};
int Game::times[6] = {999, 999, 999, 999, 999, 999};

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
    TTF_Init();

    window = new Window(title, x, y, width, height, fullScreen);
    renderer = new Renderer(window->getWindow());
    texture = new Texture("res/spritesheet.png", renderer);
    manager = new ManagerManager(renderer);
    mixer = new Mixer();
    mixer->addSfx("res/sfx/jump.wav");
    mixer->addSfx("res/sfx/hit.wav");
    mixer->addSfx("res/sfx/jump.wav");
    running = true;
  }
  else
  {
    running = false;
  }
}

void Game::close()
{
  delete window;
  delete renderer;
  delete texture;
  delete manager;

  TTF_Quit();
  SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
  SDL_Quit();
}

void Game::input()
{


  SDL_Event e;
  SDL_PollEvent(&e);
  switch (e.type)
  {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      switch (e.key.keysym.sym)
      {
        case SDLK_a:
          inputs.left = true;
          break;
        case SDLK_d:
          inputs.right = true;
          break;
        case SDLK_w:
          inputs.up = true;
          break;
        case SDLK_s:
          inputs.down = true;
          break;
      }
      break;
    case SDL_KEYUP:
      switch (e.key.keysym.sym)
      {
        case SDLK_a:
          inputs.left = false;
          break;
        case SDLK_d:
          inputs.right = false;
          break;
        case SDLK_w:
          inputs.up = false;
          break;
        case SDLK_s:
          inputs.down = false;
          break;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      switch (e.button.button)
      {
        case SDL_BUTTON_LEFT:
          inputs.attack = true;
          break;
        case SDL_BUTTON_RIGHT:
          inputs.special = true;
          break;
      }
      break;
    /*case SDL_MOUSEBUTTONUP:
      switch (e.button.button)
      {
        case SDL_BUTTON_LEFT:
          inputs.attack = false;
          break;
        case SDL_BUTTON_RIGHT:
          inputs.special = false;
          break;
      }
      break;*/
  }
  SDL_GetMouseState(&inputs.mouseX, &inputs.mouseY);
}

void Game::update()
{
  manager->update();
  gameState.updateState();
  if (gameState.getState() == GameState::QUIT)
    running = false;

    inputs.attack = false;
    inputs.special = false;
}

void Game::draw()
{
  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  manager->draw();

  renderer->present();
}

bool Game::isRunning()
{
  return running;
}

Texture* Game::getTexture()
{
  return texture;
}
