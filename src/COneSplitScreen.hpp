#ifndef CONESPLITSCREEN_H
#define CONESPLITSCREEN_H


#include "CSplitScreens.hpp"


class COneSplitScreen: public CSplitScreens {

public:

  COneSplitScreen(const CCanvas &levelCanvas, CCanvas &drawCanvas);

  virtual void Grab(const DisplayPilots &pilots) override;
  virtual void DrawRadar(const DisplayPilots &pilots) override;
};


#endif
