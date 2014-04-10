#ifndef CGAMMA_SEEK_H
#define CGAMMA_SEEK_H


#include "CSeekAndDestroy.hpp"


class CGammaSeek:public CSeekAndDestroy {

public:

 CGammaSeek(CPilotBot &pilot);


private:

 virtual void SetShootControl(CPilotInputBot &input);


};



#endif
