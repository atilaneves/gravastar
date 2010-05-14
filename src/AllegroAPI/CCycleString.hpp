#ifndef CCYCLESTRING_H
#define CCYCLESTRING_H


#include "CCycleLeaf.hpp"
#include <vector>
#include <string>


typedef std::vector<std::string> strings_t;


class CCycleString:public CCycleLeaf {

public:

  CCycleString(const std::string &title, const strings_t& strings,
	       int max, int min = 1);

  virtual std::string GetString() const { 
    return mStrings[mCycle.ToInt() - mCycle.GetMin()]; }
  

private:

 strings_t mStrings;


};


#endif
