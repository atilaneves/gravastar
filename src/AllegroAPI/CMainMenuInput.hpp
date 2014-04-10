#ifndef CMAINMENUINPUT_HPP
#define CMAINMENUINPUT_HPP


#include "CMenuInput.hpp"


class CMainMenuInput: public CMenuInput {

public:
  virtual bool Up() override;
  virtual bool Down() override;
  virtual bool Left() override;
  virtual bool Right() override;
  virtual bool Select() override;
  virtual bool Cancel() override;

private:


};

#endif
