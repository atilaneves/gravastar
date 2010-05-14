#ifndef CXBOW_SEEK_H
#define CXBOW_SEEK_H


#include "CSeekAndDestroy.hpp"


class CXbowSeek:public CSeekAndDestroy {

public:

 CXbowSeek(CPilotBot &pilot);


private:

 virtual void SetShootControl(CPilotInputBot &input);


};



#endif
