#ifndef CGRAVMEDIA_H
#define CGRAVMEDIA_H


class CGravOptions;
#include "CLevel.hpp"
#include "CShipYard.hpp"


class CGravMedia {

public:

  CGravMedia(const CGravOptions &options);

        CLevel&    GetLevel()          { return mLevel;    }
  const CShipYard& GetShipYard() const { return mShipYard; }


private:

        CLevel    mLevel;
  const CShipYard mShipYard;


};


#endif
