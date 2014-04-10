#ifndef CMENUINPUTBOT_H
#define CMENUINPUTBOT_H


#include "CMenuInput.hpp"
class CMenuInputPilot;


class CMenuInputBot: public CMenuInput {

public:

  CMenuInputBot(CMenuInputPilot &menuInputPilot);
  virtual ~CMenuInputBot() { }

  void SetActive() { mActive = true; }

  virtual bool Up();     
  virtual bool Down();   
  virtual bool Left();   
  virtual bool Right();  
  virtual bool Select(); 
  virtual bool Cancel(); 


private:

  bool mActive;

};

#endif
