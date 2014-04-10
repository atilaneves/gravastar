#ifndef CNIMBUS_SEEK_H
#define CNIMBUS_SEEK_H


#include "CSeekAndDestroy.hpp"


class CNimbusSeek:public CSeekAndDestroy {

public:

  CNimbusSeek(CPilotBot &pilot);

  virtual void SetShootControl(CPilotInputBot &input) override;
  virtual bool WantsToShoot() override;

private:

  bool mNoClearLine;

};



#endif
