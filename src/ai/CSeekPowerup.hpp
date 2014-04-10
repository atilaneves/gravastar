#ifndef CSEEK_POWERUP_H
#define CSEEK_POWERUP_H


#include "CBotAction.hpp"
class CPowerups;


class CSeekPowerup:public CBotAction {

public:

 CSeekPowerup(CPilotBot &pilot, const CPowerups &powerups);


private:

  const CPowerups& mPowerups;

  virtual void Think() override;
         int    GetBaseIndex();
         double GetNoseAngle();

};


#endif
