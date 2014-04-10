#ifndef CLUNA_SEEK_H
#define CLUNA_SEEK_H


#include "CSeekAndDestroy.hpp"


class CLunaSeek:public CSeekAndDestroy {

public:

 CLunaSeek(CPilotBot &pilot);


private:
  virtual void SetShootControl(CPilotInputBot &input) override;
};



#endif
