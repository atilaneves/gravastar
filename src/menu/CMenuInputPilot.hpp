#ifndef CMENUINPUTPILOT_H
#define CMENUINPUTPILOT_H


#include "CMenuInput.hpp"
#include "CPilotInput.hpp"
#include <memory>
#include <vector>
class CClientOptions;
class CMenuInputBot;

class CMenuInputPilot: public CMenuInput {

public:

  CMenuInputPilot(int index, const CClientOptions& options);
  virtual ~CMenuInputPilot();

  void AddBot(CMenuInputBot* bot);
  
  virtual bool Up();     
  virtual bool Down();   
  virtual bool Left();   
  virtual bool Right();  
  virtual bool Select(); 
  virtual bool Cancel(); 


private:

  std::auto_ptr<CPilotInput> mInput;
  std::vector<CMenuInputBot*> mBots;
  bool mUp, mDown, mLeft, mRight, mSelect, mCancel;

};

#endif
