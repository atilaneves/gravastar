#ifndef CNULLSONG_H
#define CNULLSONG_H


#include "CSong.hpp"


class CNullSong: public CSong {

public:

  CNullSong():CSong("") { }
  virtual void Adjust(bool loop = true) { }
  virtual void PlayLoop() { }
  virtual bool Poll() { return true; }
  virtual void Stop() { }

};

#endif
