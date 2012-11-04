#ifndef CRANDOM_SONG_H
#define CRANDOM_SONG_H


#include "CSong.hpp"
#include <string>
#include <memory>


class CRandomSong: public CSong {

public:

  CRandomSong();
  virtual ~CRandomSong() { }

  virtual void Adjust(bool loop = true) { mSong->Adjust(loop); }
  virtual void PlayLoop() { mSong->PlayLoop(); }
  virtual bool Poll() { return mSong->Poll(); }
  virtual void Stop() { mSong->Stop(); }


private:

  std::unique_ptr<CSong> mSong;

  CSong*      CreateSong()  const;
  std::string GetSongName() const;

};

#endif
