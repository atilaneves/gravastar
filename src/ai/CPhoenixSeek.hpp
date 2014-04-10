#ifndef CPHOENIX_SEEK_H
#define CPHOENIX_SEEK_H


#include "CSeekAndDestroy.hpp"


class CPhoenixSeek:public CSeekAndDestroy {

public:

 CPhoenixSeek(CPilotBot &pilot);


private:

 virtual void SetShootControl(CPilotInputBot &input);


};



#endif
