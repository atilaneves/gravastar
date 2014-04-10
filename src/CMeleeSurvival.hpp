#ifndef CMELEESURVIVAL_H
#define CMELEESURVIVAL_H


#include "CMeleeOnServer.hpp"


class CMeleeSurvival:public CMeleeOnServer {

public:

  CMeleeSurvival(const CGravOptions &options);
  virtual ~CMeleeSurvival() { }


protected:
  virtual int GetWinner() override;
  virtual bool IsGameOver() override;
};

#endif
