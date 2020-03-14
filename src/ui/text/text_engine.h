#ifndef TEXT_ENGINE
#define TEXT_ENGINE

#include <string>
#include <vector>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "game_item.h"

struct OutputSpeed
{
  int index;
  int speed;
};

struct MoveEvent
{
  int index;
  bool moving;
};

struct TextEngineDefaults
{
  int ptsize;
  const char* fontLoc;
  int speed;
  SDL_Color color;
};

struct TextEngineFont
{
  int index;
  TTF_Font* font;
  SDL_Color color;
};

struct TextEngineChar
{
  SDL_Texture* texture;
  SDL_Rect myPos;
  bool moving;
};

class TextEngine : public GameItem
{
public:
  TextEngine(Renderer*, std::string mesg, int x, int y);
  ~TextEngine();

  void update();
  void draw();
  bool finished();
  void addFont(int index, const char* fontLoc, int ptsize);
  void addFont(int index, const char* fontLoc, int ptsize, SDL_Color color);
  void addSpeed(int index, int speed);
  void setMoving(int index, bool);
private:
  void nextChar();
  void fullMessage();

  static TextEngineDefaults defaults;

  std::string wholeMessage;
  std::string message;
  int currentChar;
  int currentSpeed;
  int currentFont;
  bool moving;
  int messageX, messageY, currentX, currentY;
  std::vector<OutputSpeed> outputSpeeds;
  std::vector<TextEngineFont> fonts;
  std::vector<MoveEvent> moveEvents;
  std::vector<int> charTicks;
  std::vector<TextEngineChar> chars;
};

#endif
