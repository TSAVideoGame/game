#include "text_engine.h"
#include "constants.h"
#include <cmath>

TextEngineDefaults TextEngine::defaults = {16, "res/Roboto_Mono/RobotoMono-Regular.ttf", 2, {0, 0, 0}};

static int ticks = 0; // For demonstration

TextEngine::TextEngine(Renderer* ren, std::string mesg, int x, int y) : GameItem(ren)
{
  wholeMessage = mesg;
  message = wholeMessage[0];
  currentChar = 0;
  currentSpeed = defaults.speed;
  currentFont = 0;
  currentX = messageX = x;
  currentY = messageY = y;
  charTicks.push_back(0);
  moving = false;
}

TextEngine::~TextEngine()
{
  for (auto font : fonts)
    TTF_CloseFont(font.font);

  for (auto text : chars)
    SDL_DestroyTexture(text.texture);
}

/*
 * You can (and probably should) change this function to match your program
 */
void TextEngine::update()
{
  for (int i = 0; i < charTicks.size(); i++)
    charTicks[i]++;

  // This segment can probably be optimized
  for (auto os : outputSpeeds)
  {
    if (currentChar == os.index)
    {
      currentSpeed = os.speed;
      break;
    }
  }

  for (int i = 0; i < fonts.size(); i ++)
  {
    if (currentChar == fonts[i].index)
    {
      currentFont = i;
      break;
    }
  }

  for (int i = 0; i < moveEvents.size(); i++)
  {
    if (currentChar == moveEvents[i].index)
    {
      moving = moveEvents[i].moving;
      break;
    }
  }

  ticks++;
  if (ticks % currentSpeed == 0)
    nextChar();
}

void TextEngine::draw()
{
  /*
   * Multi-fonts not supported yet
   * Just using the first font available
   * I will need to redo the smart wrap code and a lot of other code
   */
  if (fonts.size() == 0)
    fonts.push_back({0, TTF_OpenFont(defaults.fontLoc, defaults.ptsize), defaults.color});

  if (chars.size() < message.length() && chars.size() < wholeMessage.size())
  {
    // Blended looks nicer than Solid, looks are priority
    SDL_Surface* txtSurface = TTF_RenderText_Blended(fonts[currentFont].font, message.substr(chars.size(), 1).c_str(), fonts[currentFont].color); // 1200 is window width
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->getRenderer(), txtSurface);

    chars.push_back({texture, {currentX, currentY, txtSurface->w, txtSurface->h}, moving});

    currentX += txtSurface->w;
    if (currentX > WINDOW_WIDTH - 32 || message[currentChar] == '\n')
    {
      currentX = messageX;
      currentY += txtSurface->h;
    }

    SDL_FreeSurface(txtSurface);
  }

  for (int i = 0; i < chars.size(); i++)
  {
    SDL_Rect dRect;
    if (chars[i].moving)
      dRect = {chars[i].myPos.x, chars[i].myPos.y + (int) (4 * std::sin(charTicks[i] * 100)), chars[i].myPos.w, chars[i].myPos.h};
    else
      dRect = chars[i].myPos;
    SDL_RenderCopy(renderer->getRenderer(), chars[i].texture, NULL, &dRect);
  }

}

void TextEngine::nextChar()
{
  if (currentChar < wholeMessage.length())
    currentChar++;

  /*
   * Smart Wrap
   * Checks if there is enough space for the next word
   * All 'words' are substrings seperated by spaces
   */
  if (wholeMessage[currentChar] == ' ') // New word is approaching
  {
    int totalWidth = 0;
    for (auto text : chars)
      totalWidth += text.myPos.w;
    int charWidth = totalWidth / currentChar; // This is approximate, should be good enough
    int wordLen = wholeMessage.find(" ", currentChar + 1) - (currentChar + 1); // wordLen = index of new ' ' - index of first letter of word
    if (wordLen < 0) // Last word
      wordLen = wholeMessage.length() - (currentChar + 1);

    if (wordLen * charWidth + (messageX + currentX) > WINDOW_WIDTH - 32) // if the new word will be greater than the width which will wrap
    {
      message += '\n';
    }
    else
    {
      message += ' ';
    }
  }
  else
    message += wholeMessage[currentChar];

  charTicks.push_back(0);
}

void TextEngine::fullMessage()
{
  message = wholeMessage;
  while (charTicks.size() != wholeMessage.length())
    charTicks.push_back(0);
}

bool TextEngine::finished()
{
  return currentChar == wholeMessage.length();
}

void TextEngine::addSpeed(int index, int speed)
{
  outputSpeeds.push_back({index, speed});
}

void TextEngine::addFont(int index, const char* fontLoc, int ptsize)
{
  fonts.push_back({index, TTF_OpenFont(fontLoc, ptsize), defaults.color});
}

void TextEngine::addFont(int index, const char* fontLoc, int ptsize, SDL_Color color)
{
  fonts.push_back({index, TTF_OpenFont(fontLoc, ptsize), color});
}

void TextEngine::setMoving(int index, bool moving)
{
  moveEvents.push_back({index, moving});
}
