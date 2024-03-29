#ifndef CDISCUS_SEEK_H
#define CDISCUS_SEEK_H


#include "CSeekAndDestroy.hpp"
#include "CTimeCounter.hpp"


class CDiscusSeek:public CSeekAndDestroy {

public:

  CDiscusSeek(CPilotBot &pilot);

  virtual bool WantsToShoot() override { return mShieldCounter.IsActive(); }

private:

  CTimeCounter mShieldCounter;

  virtual void SetShootControl(CPilotInputBot &input) override;
  virtual void Think() override;
};



#endif
