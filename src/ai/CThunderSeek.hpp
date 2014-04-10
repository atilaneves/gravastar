#ifndef CTHUNDER_SEEK_H
#define CTHUNDER_SEEK_H


#include "CSeekAndDestroy.hpp"


class CThunderSeek:public CSeekAndDestroy {

public:

 CThunderSeek(CPilotBot &pilot);


private:

 virtual void SetShootControl(CPilotInputBot &input);


};



#endif
