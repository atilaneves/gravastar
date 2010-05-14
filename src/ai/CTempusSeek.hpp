#ifndef CTEMPUS_SEEK_H
#define CTEMPUS_SEEK_H


#include "CSeekAndDestroy.hpp"


class CTempusSeek:public CSeekAndDestroy {

public:

 CTempusSeek(CPilotBot &pilot);

  virtual void Think();


private:

  bool mDetonate;

 virtual void SetShootControl(CPilotInputBot &input);


};



#endif
