#include "CMeleeFragNb.hpp"
#include "CMeleeFactory.hpp"
#include "CMeleeScore.hpp"
#include "CSound.hpp"
#include "CPilot.hpp"
#include <stdio.h>


REG_MELEE("Frag Limit", CMeleeFragNb)


CMeleeFragNb::CMeleeFragNb(const CGravOptions &options):
  CMeleeOnServer(options),
  mWinner(-1) {

  mSounds["Blue"]   = new CSound("nearly0");
  mSounds["Red"]    = new CSound("nearly1");
  mSounds["Green"]  = new CSound("nearly2");
  mSounds["Yellow"] = new CSound("nearly3");
}


CMeleeFragNb::~CMeleeFragNb() {
  for(soundPlace_t i = mSounds.begin(); i != mSounds.end(); ++i)
    delete (*i).second;
}


bool CMeleeFragNb::IsGameOver() {

  auto pilots = GetActivePilots();
  if(pilots.empty()) return -1;
  int fragLimit = pilots[0]->GetNbShips();
  int winTeam = -1;
  std::string tNames[] = {"Blue", "Red", "Green", "Yellow"};
  std::map<std::string, int> teams;
  for(int t = 0; t < kMaxNbTeams; t++) teams[tNames[t]] = 0;

  for(unsigned int p = 0; p < pilots.size(); p++) {
    std::string name = pilots[p]->GetTeam().GetName();
    teams[name] = teams[name] + pilots[p]->GetScore();
  }

  //find winning team
  for(int t = 0; t < kMaxNbTeams; t++) {
    if(teams[tNames[t]] >= fragLimit) {
      winTeam = winTeam == -1 ? t : -2;
      if(!mPlayedSounds[t] && teams[tNames[t]] == fragLimit-1) {
	mSounds[tNames[t]]->PlayCentre(); //warn the players
	mPlayedSounds[t] = true; //don't play it again
      }
    }
  }
  //return 1st player we find from the winning team
  if(winTeam != -1)
    for(unsigned int p = 0;  p < pilots.size(); p++)
      if(pilots[p]->GetTeam().GetName() == tNames[winTeam] && mWinner == -1)
	mWinner = p;

  return mWinner != -1;
}


int CMeleeFragNb::GetWinner() {
 return mWinner;
}
