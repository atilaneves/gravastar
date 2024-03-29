#ifndef CCYCLE_STRING_ENTER_H
#define CCYCLE_STRING_ENTER_H


#include "CCycleString.hpp"


class CCycleStringEnter: public CCycleString {

public:

  CCycleStringEnter(const std::string &title, const strings_t& strings,
                    int max, int min = 1);


protected:
  virtual void Left() override {}
  virtual void Right() override {}
  virtual void Run(CRootMenu &rootMenu) override { LeafAction(1); }
};


#endif
