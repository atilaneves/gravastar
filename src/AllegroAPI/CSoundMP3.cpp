#include "CSoundMP3.hpp"
#include "CBinaryFile.hpp"
#include "CDataFile.hpp"
#include <algorithm>
#include <allegro.h>
#include <stdio.h>


float CSoundMP3::sVolume=1;
std::list<CSoundMP3*> CSoundMP3::sMP3s;


CSoundMP3::CSoundMP3(const std::string &fileName):
  CSong(fileName) {
  mFile = new CBinaryFile(CDataFile::GetFileName("Music/" + fileName + ".mp3"));
  mMP3 = almp3_create_mp3(mFile->GetData(),mFile->GetLength());
  sMP3s.push_back(this);
}


CSoundMP3::~CSoundMP3() {
  Stop();
  almp3_destroy_mp3(mMP3);
  delete mFile;
  mp3Place_t where = std::find(sMP3s.begin(), sMP3s.end(), this);
  if(where != sMP3s.end()) sMP3s.erase(where);
}


void CSoundMP3::Play() {
  int pan = 128, speed = 1000, loop = 0;
  almp3_play_ex_mp3(mMP3,kBufferSize,int(sVolume*255),pan,speed,loop);
}


void CSoundMP3::PlayLoop() {
  int pan =128, speed=1000,loop=1;
  almp3_play_ex_mp3(mMP3, kBufferSize, int(sVolume*255), pan, speed, loop);
}


bool CSoundMP3::Poll() {
  return almp3_poll_mp3(mMP3) == ALMP3_OK;
}


void CSoundMP3::Stop() {
  almp3_stop_mp3(mMP3);
  almp3_rewind_mp3(mMP3);
}


void CSoundMP3::Adjust(bool loop) {
  const int pan = 128, speed = 1000;
  almp3_adjust_mp3(mMP3, int(sVolume*255), pan, speed, int(loop));
}


void CSoundMP3::SetMasterVolume(float v) {
  if(v >= 0 && v <= 1) sVolume = v; 
  for(mp3Place_t i = sMP3s.begin(); i != sMP3s.end(); ++i)
    (*i)->Adjust();
}
