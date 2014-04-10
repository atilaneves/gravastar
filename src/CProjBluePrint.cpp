#include "CProjBluePrint.hpp"
#include "CDataFile.hpp"
#include "projectiledat.h"


CProjBluePrint::CProjBluePrint(const std::string &name, const CTeam &team):
  mDataFile(new CDataFile("Weapons/" + name + ".dat")),
  mTeam(team),
  mExplosiveBluePrint(FRAME000, name, *mDataFile, team),
  mStatSprite(mDataFile->GetData(FRAME000), team), mSound(name),
  mShadowBluePrint(FRAME000, *mDataFile, team, team.GetMainColour()) {

  SetAttributes((char*)mDataFile->GetData(ATTRIBUTES));
  delete mDataFile;

}


void CProjBluePrint::SetAttributes(char *data) {
  sscanf(data, "%*s %*s %*s %*s %f %f %f %f",
	 &mMaxDamage, &mMaxHull, &mShockWaveForce, &mMass);
}
