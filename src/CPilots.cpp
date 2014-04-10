#include "CPilots.hpp"
#include "CPilot.hpp"
#include "CLevel.hpp"


std::vector<CPilot*> CPilots::sPilots;



bool CPilots::IsAlone(CPilot& pilot) {

  for (auto &sPilot : sPilots) {
    if (sPilot->IsAlive() && sPilot->GetShip().IsAlive() &&
        sPilot->GetTeam() != pilot.GetTeam())
            return false;
    }

    return true; //all alone...
}


bool CPilots::IsCoastClear(CPilot &pilot) { //ab near?

    if(IsAlone(pilot)) return true; //as is obvious
    for (auto &sPilot : sPilots) {
      if (sPilot->IsAlive() && sPilot->GetShip().IsAlive() &&
          sPilot->GetTeam() != pilot.GetTeam()) {

            const CVector2& pos1 = pilot.GetShip().GetPos();
            const CVector2 &pos2 = sPilot->GetShip().GetPos();
            if(pilot.GetShip().GetLevel().IsClearLine(pos1, pos2))
                return false; //can't be clear if they can take a shot!

            const int kMinDistance = 150;
            if((pos1 - pos2).Radius() < kMinDistance)
                return false; //they're too close for it to be clear
        }
    }

    return true; //nb near, coast is clear
}


int CPilots::GetNbLivePilots() {
    int nbPilots = 0;
    for (auto &sPilot : sPilots)
      if (sPilot->IsAlive())
        nbPilots++;
    return nbPilots;
}
