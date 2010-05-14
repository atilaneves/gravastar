#ifndef CMELEEFRAGNB_H
#define CMELEEFRAGNB_H


#include "CMelee.hpp"
#include <map>
class CSound;


class CMeleeFragNb:public CMelee {

public:

  CMeleeFragNb(const CGravOptions &options);
  virtual ~CMeleeFragNb();


private:

  enum { kMaxNbTeams = 4 };

  int mWinner;
  bool mPlayedSounds[kMaxNbTeams];
  std::map<std::string, CSound*> mSounds;

  virtual int  GetWinner();
  virtual bool IsGameOver();


};

#endif
