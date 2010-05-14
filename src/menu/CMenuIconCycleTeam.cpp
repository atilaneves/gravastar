#include "CMenuIconCycleTeam.hpp"
#include "CFont.hpp"
#include "CCycleTeam.hpp"
#include "CTeam.hpp"



CMenuIconCycleTeam::CMenuIconCycleTeam(const std::string &title,
				       const CCycleTeam &cycleMenu):
  CMenuIconCycle(title, cycleMenu),
  mCycleTeam(cycleMenu) {

  
}


void CMenuIconCycleTeam::Draw(CCanvas &canvas, int x, int y, bool highlight) {
  mTitle.Draw(canvas, x, y, highlight);
  mFont.Print(canvas, x + mTitle.GetWidth() + 10, y,
	      mCycleTeam.GetTeam().GetDarkColour(), -1,
	      mCycleTeam.GetString());
}


