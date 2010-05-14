#ifndef CMENUINPUTPILOT_H
#define CMENUINPUTPILOT_H


#include "CMenuInput.hpp"
#include "CPilotInput.hpp"
#include <memory>
class CGravOptions;


class CMenuInputPilot: public CMenuInput {

public:

  CMenuInputPilot(int index, const CGravOptions& options);
  virtual ~CMenuInputPilot() { }

  virtual bool Up();     
  virtual bool Down();   
  virtual bool Left();   
  virtual bool Right();  
  virtual bool Select(); 
  virtual bool Cancel(); 


private:

  std::auto_ptr<CPilotInput> mInput;
  bool mUp, mDown, mLeft, mRight, mSelect, mCancel;

};

#endif
