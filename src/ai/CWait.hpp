#ifndef CWAIT_H
#define CWAIT_H


#include "CBotAction.hpp"


class CWait:public CBotAction {

public:

 CWait(CPilotBot &pilot);


private:
  virtual void Think() override;
};


#endif
