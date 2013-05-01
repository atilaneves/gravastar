#ifndef CGRAVMEDIA_H
#define CGRAVMEDIA_H


class CMeleeOptions;
#include "CLevel.hpp"
#include "CShipYard.hpp"
#include "CClientOptions.hpp"


class CGravMedia {

public:

    CGravMedia(const CMeleeOptions &meleeOptions,
               const CClientOptions::AllPilotOptions& allPilotOptions);

        CLevel&    GetLevel()          { return mLevel;    }
  const CShipYard& GetShipYard() const { return mShipYard; }


private:

        CLevel    mLevel;
  const CShipYard mShipYard;


};


#endif
