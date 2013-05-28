#ifndef CMELEEFRAGNB_H
#define CMELEEFRAGNB_H


#include "CMeleeOnServer.hpp"
#include <map>
class CSound;


class CMeleeFragNb:public CMeleeOnServer {

public:

  CMeleeFragNb(const CGravOptions &options);
  virtual ~CMeleeFragNb();


private:

  enum { kMaxNbTeams = 4 };

  int mWinner;
  bool mPlayedSounds[kMaxNbTeams];
  std::map<std::string, CSound*> mSounds;

  virtual int  GetWinner() override;
  virtual bool IsGameOver() override;
};

#endif
