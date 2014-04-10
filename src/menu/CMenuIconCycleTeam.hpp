#ifndef CMENU_ICON_CYCLE_TEAMH
#define CMENU_ICON_CYCLE_TEAMH


#include "CMenuIconCycle.hpp"
class CCycleTeam;


class CMenuIconCycleTeam:public CMenuIconCycle {

public:
  
  CMenuIconCycleTeam(const std::string &title, const CCycleTeam &cycleMenu);
  virtual ~CMenuIconCycleTeam() { }
  
  
private:

  const CCycleTeam &mCycleTeam;

  virtual void Draw(CCanvas &canvas, int x, int y, bool highlight = false) const override;
  
};

#endif
