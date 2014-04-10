#ifndef CSOUND_H
#define CSOUND_H


#include <string>
#include <allegro.h>
#include "CVector2.hpp"



typedef SAMPLE Sample_t;


class CSound {

public:

  CSound(const std::string &name, float volume=1, float frequency=1);
  CSound(const CSound &sound);
  ~CSound();

         void  Adjust(const CVector2 &pos);
  static float GetMasterVolume() { return sMasterVolume; }
         bool  IsPlaying() const { return mIsPlaying; }
         void  Play(const CVector2 &pos, float volume=1, bool loop=false);
         void  PlayCentre(float volume=1, bool loop=false);
  static void  SetMasterVolume(float v) { sMasterVolume=v; }
  static void  SetMaxX(int x)           { sMaxX=x; }
         void  Stop();


private:

  static int   sMaxX;
  static float sMasterVolume;

  bool      mDeleteSample;
  bool      mIsPlaying;
  float     mVolume;
  float     mFrequency;
  Sample_t *mSample;

  int GetPan(float x);
  int GetVolume(const CVector2 &pos, float volume=1);
  int IntFreq() const { return int(mFrequency*1000); }

};

#endif
