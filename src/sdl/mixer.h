#ifndef MIXER
#define MIXER

#include <SDL2/SDL_mixer.h>
#include <vector>

class Mixer
{
public:
  Mixer();
  ~Mixer();
  void play(int);
  void pause();
  void stop();
  void addTrack(const char* fpath);
  void playSfx(int);
  void addSfx(const char* fpath);
  void setMusicVolume(int);
  static int maxVolume;
  static int minVolume;
private:
  std::vector<Mix_Music*> music;
  std::vector<Mix_Chunk*> sfx;
};


#endif
