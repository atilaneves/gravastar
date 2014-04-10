#include "CMeleeFragTime.hpp"
#include "CMeleeFactory.hpp"
#include "CMeleeScore.hpp"
#include "CRadar.hpp"
#include "CSound.hpp"
#include "CPilot.hpp"
#include <stdio.h>


REG_MELEE("Time Limit", CMeleeFragTime)


CMeleeFragTime::CMeleeFragTime(const CGravOptions &options):
  CMeleeOnServer(options),
  mPlayedWarning30(false), mPlayedWarning10(false),
  mWarning30("30seconds"), mWarning10("10seconds") {

  mTimeCounter.Start(60 * mPilots[0]->GetNbShips());
}


bool CMeleeFragTime::IsGameOver() {
 if(!mPlayedWarning30 && mTimeCounter.TimeLeft() < 30) {
    mWarning30.PlayCentre();
    mPlayedWarning30 = true; //only do it once
 }
 if(!mPlayedWarning10 && mTimeCounter.TimeLeft() < 10) {
    mWarning10.PlayCentre();
    mPlayedWarning10 = true; //only do it once
 }

 return !mTimeCounter.IsActive();
}


int CMeleeFragTime::GetWinner() {

  auto pilots = GetActivePilots();
  if(pilots.empty()) return -1;
  int winTeam = -1;
  std::string tNames[] = {"Blue", "Red", "Green", "Yellow"};
  std::map<std::string, int> teams;
  for (auto &tName : tNames)
    teams[tName] = 0;

  for (auto &pilot : pilots) {
    std::string name = pilot->GetTeam().GetName();
    teams[name] = teams[name] + pilot->GetScore();
  }

  //find winning team
  int max = -1;
  for(int t = 0; t < kMaxNbTeams; t++) {
    if(teams[tNames[t]] > max) {
      max = teams[tNames[t]];
      winTeam = t;
    }
  }

  for(int t = winTeam + 1; t < kMaxNbTeams; t++)
    if(teams[tNames[t]] == max) return -1; //2 teams are tied

  //return 1st player we find from the winning team
  if(winTeam != -1)
    for(unsigned int p = 0;  p < pilots.size(); p++)
      if(pilots[p]->GetTeam().GetName() == tNames[winTeam]) {
        return p;
      }

  return  -1;
}
