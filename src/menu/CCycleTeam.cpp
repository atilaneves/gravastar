#include "CCycleTeam.hpp"
#include "CMenuIconCycleTeam.hpp"
#include "CTeam.hpp"
#include "CFont.hpp"


static const std::string gNames[] = {"Blue", "Red", "Green", "Yellow"};


CCycleTeam::CCycleTeam(const std::string &title):
  CCycleString(title,
	       strings_t(gNames, 
			 gNames + sizeof(gNames) / sizeof(std::string)),
	       3, 0) {

  AdoptIcon(new CMenuIconCycleTeam(title, *this));
}


const CTeam& CCycleTeam::GetTeam() const {
  return CTeam::FindByName(GetString());
}
