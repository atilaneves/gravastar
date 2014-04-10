#ifndef CTEMPUS_SEEK_H
#define CTEMPUS_SEEK_H


#include "CSeekAndDestroy.hpp"


class CTempusSeek:public CSeekAndDestroy {

public:

 CTempusSeek(CPilotBot &pilot);

 virtual void Think() override;

private:

  bool mDetonate;

  virtual void SetShootControl(CPilotInputBot &input) override;
};



#endif
