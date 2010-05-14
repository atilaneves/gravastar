#ifndef CMAINMENUINPUT_HPP
#define CMAINMENUINPUT_HPP


#include "CMenuInput.hpp"


class CMainMenuInput: public CMenuInput {

public:

  virtual bool Up();
  virtual bool Down();
  virtual bool Left();
  virtual bool Right();
  virtual bool Select();
  virtual bool Cancel();


private:


};

#endif
