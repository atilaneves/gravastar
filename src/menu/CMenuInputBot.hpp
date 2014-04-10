#ifndef CMENUINPUTBOT_H
#define CMENUINPUTBOT_H


#include "CMenuInput.hpp"
class CMenuInputPilot;


class CMenuInputBot: public CMenuInput {

public:

  CMenuInputBot(CMenuInputPilot &menuInputPilot);
  virtual ~CMenuInputBot() { }

  void SetActive() { mActive = true; }

  virtual bool Up() override;
  virtual bool Down() override;
  virtual bool Left() override;
  virtual bool Right() override;
  virtual bool Select() override;
  virtual bool Cancel() override;

private:

  bool mActive;

};

#endif
