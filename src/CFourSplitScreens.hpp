#ifndef CFOURSPLITSCREENS_H
#define CFOURSPLITSCREENS_H


#include "CSplitScreens.hpp"


class CFourSplitScreens: public CSplitScreens {

public:

  CFourSplitScreens(const CCanvas &levelCanvas, CCanvas &drawCanvas);

  virtual void Grab(const DisplayPilots& pilots);
  virtual void DrawRadar(const DisplayPilots& pilots);


private:


};


#endif
