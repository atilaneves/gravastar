#include "CMeleeSurvival.hpp"
#include "CMeleeFactory.hpp"
#include "CPilot.hpp"
#include <map>


REG_MELEE("Survival", CMeleeSurvival)
REG_MELEE2("Squad",   CMeleeSurvival)


CMeleeSurvival::CMeleeSurvival(const CGravOptions &options):
  CMeleeOnServer(options) {
}


bool CMeleeSurvival::IsGameOver() {
  if(mPilots.size() == 1) return false; //game doesn't end w just 1 player
  const int kMaxNbTeams = 4;
  std::string tNames[kMaxNbTeams] = {"Blue", "Red", "Green", "Yellow"};
  std::map<std::string, int> teams;
  for (auto &tName : tNames)
    teams[tName] = 0;
  auto pilots = GetActivePilots();
  for (auto &pilot : pilots) {
    std::string name = pilot->GetTeam().GetName();
    teams[name] = teams[name] + 1;
  }
  int nbTeams = 0;
  for (auto &tName : tNames)
    if (teams[tName])
      nbTeams++;

  return nbTeams == 1; //only one team left, game over
}


int CMeleeSurvival::GetWinner() {
  int winner = -1; //nobody
  const auto pilots = GetActivePilots();
  if(pilots.size() > 0) winner = pilots[0]->GetIndex();
  return winner;
}
