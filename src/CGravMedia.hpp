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
    ~CGravMedia();

        CLevel&    GetLevel()          { return mLevel;    }
  const CShipYard& GetShipYard() const { return mShipYard; }


private:

          bool    mHashing; //just to guarantee this gets initialised 1st
        CLevel    mLevel;
  const CShipYard mShipYard;


};


#endif
