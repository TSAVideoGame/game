#include "mixer.h"

int Mixer::maxVolume = MIX_MAX_VOLUME;
int Mixer::minVolume = 0;

Mixer::Mixer()
{
  Mix_Volume(-1, maxVolume / 4);
}

Mixer::~Mixer()
{
  for (auto track : music)
    Mix_FreeMusic(track);
}

void Mixer::play(int i)
{
  Mix_PlayMusic(music[i], -1);
}

void Mixer::pause()
{
  Mix_PauseMusic();
}

void Mixer::stop()
{
  Mix_HaltMusic();
}

void Mixer::addTrack(const char* fpath)
{
  music.push_back(Mix_LoadMUS(fpath));
}

void Mixer::playSfx(int i)
{
  Mix_PlayChannel(-1, sfx[i], 0);
}

void Mixer::addSfx(const char *fpath)
{
  sfx.push_back(Mix_LoadWAV(fpath));
}

void Mixer::setMusicVolume(int v)
{
  Mix_VolumeMusic(v);
}
