#ifndef CMELEESURVIVAL_H
#define CMELEESURVIVAL_H


#include "CMelee.hpp"


class CMeleeSurvival:public CMelee {

public:

  CMeleeSurvival(const CGravOptions &options);
  virtual ~CMeleeSurvival() { }


protected:

  virtual int  GetWinner();
  virtual bool IsGameOver();

};

#endif
