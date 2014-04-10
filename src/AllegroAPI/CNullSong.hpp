#ifndef CNULLSONG_H
#define CNULLSONG_H


#include "CSong.hpp"


class CNullSong: public CSong {

public:

  CNullSong():CSong("") { }
  virtual void Adjust(bool loop = true) override {}
  virtual void PlayLoop() override {}
  virtual bool Poll() override { return true; }
  virtual void Stop() override {}
};

#endif
