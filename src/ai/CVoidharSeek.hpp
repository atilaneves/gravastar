#ifndef CVOIDHAR_SEEK_H
#define CVOIDHAR_SEEK_H


#include "CSeekAndDestroy.hpp"


class CVoidharSeek:public CSeekAndDestroy {

public:

 CVoidharSeek(CPilotBot &pilot);


private:

 virtual void SetShootControl(CPilotInputBot &input);


};



#endif
