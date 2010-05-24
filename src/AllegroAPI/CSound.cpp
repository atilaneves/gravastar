#include "CSound.hpp"
#include "CDataFile.hpp"
#include <stdio.h>
#include <math.h>


int   CSound::sMaxX = 0;
float CSound::sMasterVolume = 1;


CSound::CSound(const std::string &name, float volume, float frequency):
   mDeleteSample(true), mIsPlaying(false),
   mVolume(volume), mFrequency(frequency) {

 std::string fileName = CDataFile::GetFileName("Sounds/" + name + ".wav");
 mSample = load_sample(fileName.c_str());
 if(mSample == NULL)
    fprintf(stderr,"*** Error: Unable to open %s ***\n\n",fileName.c_str());

 if(mVolume > 1) mVolume=1;

}


CSound::CSound(const CSound &sound):
  mDeleteSample(false), mIsPlaying(false), mVolume(sound.mVolume),
  mFrequency(sound.mFrequency), mSample(sound.mSample) {

}


CSound::~CSound() {
 if(mDeleteSample) destroy_sample(mSample);
}


void CSound::Play(const CVector2 &pos, float volume, bool loop) {
 if(!mIsPlaying) {
    int vol = GetVolume(pos, volume);
    if(vol>0.01) play_sample(mSample, vol, GetPan(pos.GetX()),IntFreq(),loop); 
    if(loop) mIsPlaying = true;
 }
}

void CSound::PlayCentre(float volume, bool loop) {
 if(volume > 1) volume=1;
 if(volume > 0.01)
    play_sample(mSample,int(volume*mVolume*sMasterVolume*255),128,1000,loop);
}


void CSound::Stop() {
 stop_sample(mSample);
 mIsPlaying = false;
}


void CSound::Adjust(const CVector2 &pos) {
  int loop = 0;
  if(mIsPlaying) loop = 1;
  adjust_sample(mSample, GetVolume(pos), GetPan(pos.GetX()), IntFreq(), loop);
}


int CSound::GetPan(float x) {
  float width = 0.71; //stereo width
  float left  = 0.5 - width/2; //leftmost it gets
  return int((left + width*(x/sMaxX))*255); //0.25 to 0.75
}


int CSound::GetVolume(const CVector2 &pos, float volume) {
  if(volume > 1) volume=1;
  volume *= sMasterVolume*mVolume;
  //volume *= exp(-CPilotMan::Nearest(pos)/365); //decay exp.
  return int(volume*255);
  
}
