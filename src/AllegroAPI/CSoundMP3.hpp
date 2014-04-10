#ifndef CSOUND_MP3_H
#define CSOUND_MP3_H


#include "CSong.hpp"
#include "almp3.h"
#include <string>
#include <list>
class CBinaryFile;


class CSoundMP3: public CSong {

public:

  enum { kBufferSize=65536 };

  CSoundMP3(const std::string &fileName);
  virtual ~CSoundMP3();

  virtual void Adjust(bool loop = true) override;
          void Play();
          virtual void PlayLoop() override;
          virtual bool Poll() override;
          virtual void Stop() override;
  static void SetMasterVolume(float v);


private:
 
  CBinaryFile* mFile;
  ALMP3_MP3*   mMP3;
  static float sVolume;
  static std::list<CSoundMP3*> sMP3s;

};

typedef std::list<CSoundMP3*>::iterator mp3Place_t;

#endif
