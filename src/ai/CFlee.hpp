#ifndef CFLEE_H
#define CFLEE_H


#include "CBotAction.hpp"
class CBase;


class CFlee:public CBotAction {

public:

 CFlee(CPilotBot &pilot);

 virtual void Think();


private:

  int    GetBaseIndex() const;
  bool   IsJustAboveBase(const CBase& base) const;
  void   SetDefaults();

};


#endif
