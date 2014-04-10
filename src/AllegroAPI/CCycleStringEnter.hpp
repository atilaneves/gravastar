#ifndef CCYCLE_STRING_ENTER_H
#define CCYCLE_STRING_ENTER_H


#include "CCycleString.hpp"


class CCycleStringEnter: public CCycleString {

public:

  CCycleStringEnter(const std::string &title, const strings_t& strings,
		    int max, int min = 1);


protected:

  virtual void Left()  { }
  virtual void Right() { }
  virtual  void Run(CRootMenu &rootMenu) { LeafAction(1); }


};


#endif
