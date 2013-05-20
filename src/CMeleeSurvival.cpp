#include "CMeleeSurvival.hpp"
#include "CMeleeFactory.hpp"
#include "CRadar.hpp" //pilots_t
#include "CPilot.hpp"
#include <map>


REG_MELEE("Survival", CMeleeSurvival)
REG_MELEE2("Squad",   CMeleeSurvival)


CMeleeSurvival::CMeleeSurvival(const CGravOptions &options):
  CMelee(options) {
}


bool CMeleeSurvival::IsGameOver() {
  if(mPilots.size() == 1) return false; //game doesn't end w just 1 player
  const int kMaxNbTeams = 4;
  std::string tNames[kMaxNbTeams] = {"Blue", "Red", "Green", "Yellow"};
  std::map<std::string, int> teams;
  for(int t = 0; t < kMaxNbTeams; t++) teams[tNames[t]] = 0;
  auto pilots = GetActivePilots();
  for(unsigned int p = 0; p < pilots.size(); p++) {
    std::string name = pilots[p]->GetTeam().GetName();
    teams[name] = teams[name] + 1;
  }
  int nbTeams = 0;
  for(int t = 0; t < kMaxNbTeams; t++) if(teams[tNames[t]]) nbTeams++;

  return nbTeams == 1; //only one team left, game over
}


int CMeleeSurvival::GetWinner() {
  int winner = -1; //nobody
  const auto pilots = GetActivePilots();
  if(pilots.size() > 0) winner = pilots[0]->GetIndex();
  return winner;
}
