#ifndef CTWOSPLITSCREENS_H
#define CTWOSPLITSCREENS_H


#include "CSplitScreens.hpp"


class CTwoSplitScreens: public CSplitScreens {

public:

  CTwoSplitScreens(const CCanvas &levelCanvas, CCanvas &drawCanvas);

  virtual void Grab(const DisplayPilots &pilots) override;
  virtual void DrawRadar(const DisplayPilots &pilots) override;

private:


};


#endif
