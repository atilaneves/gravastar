#ifndef CONESPLITSCREEN_H
#define CONESPLITSCREEN_H


#include "CSplitScreens.hpp"


class COneSplitScreen: public CSplitScreens {

public:

  COneSplitScreen(const CCanvas &levelCanvas, CCanvas &drawCanvas);

  virtual void Grab(const pilots_t& pilots);
  virtual void DrawRadar(const pilots_t& pilots);
};


#endif
