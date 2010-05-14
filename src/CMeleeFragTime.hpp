#ifndef CMELEEFRAGTIME_H
#define CMELEEFRAGTIME_H


#include "CMelee.hpp"
#include "CTimeCounter.hpp"
class CSound;


class CMeleeFragTime:public CMelee {

public:

  CMeleeFragTime(const CGravOptions &options);
  virtual ~CMeleeFragTime() { }


private:

  enum { kMaxNbTeams = 4 };

  bool mPlayedWarning30, mPlayedWarning10;
  CSound mWarning30, mWarning10;
  CTimeCounter mTimeCounter;

  virtual int  GetWinner();
  virtual bool IsGameOver();


};

#endif
