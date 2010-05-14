#ifndef CCYCLELEAF_H
#define CCYCLELEAF_H


#include "CMenu.hpp"
#include "CIntWrap.hpp"
#include <string>
class CMenuIconCycle;


class CCycleLeaf: public CMenu {

public:
  
  CCycleLeaf(const std::string& title, int max, int min = 1);
  
  int  		       GetCycle() const { return mCycle.ToInt();  }
  int  		       GetMax()   const { return mCycle.GetMax(); }
  int  		       GetMin()   const { return mCycle.GetMin(); }
  virtual std::string  GetString() const;
  const   std::string& GetTitle() const { return mTitle; }
          void         SetCycle(int c)  { mCycle = c; }
          void         SetIconTitle(const std::string& title);
  
  
protected:
  
  CIntWrap mCycle;
  
  void LeafAction(int delta);
  
  
private:
  
  std::string mTitle;
  CMenuIconCycle* mIconCycle;

  virtual void Left()  { LeafAction(-1); }
  virtual void Right() { LeafAction(1);  }

};



#endif
