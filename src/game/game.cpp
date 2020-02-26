#include "game.h"
#include "game_states.h"
#include <SDL2/SDL_mixer.h>

GameInput Game::inputs = {false, false, false, false, false, false, 0, 0};
bool Game::running = true;
Window* Game::window;
Renderer* Game::renderer;
Texture* Game::texture;
ManagerManager* Game::manager;
Camera Game::camera = {0, 0};
LevelInfo Game::levelInfo = {0, 0, 1, 2, false, false};
int Game::scores[5] = {0, 0, 0, 0, 0};
int Game::times[5] = {999, 999, 999, 999, 999};

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);


    window = new Window(title, x, y, width, height, fullScreen);
    renderer = new Renderer(window->getWindow());
    texture = new Texture("res/spritesheet.png", renderer);
    manager = new ManagerManager(renderer);
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
  GameStates::updateState();
  if (GameStates::getState() == GameState::QUIT)
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
