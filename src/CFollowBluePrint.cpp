#include "CFollowBluePrint.hpp"
#include "CDataFile.hpp"
#include "projectiledat.h"


CFollowBluePrint::CFollowBluePrint(const std::string &name, const CTeam &team):
  mDataFile(new CDataFile("Weapons/" + name + ".dat")),
  mTeam(team),
  mMoverBluePrint(FRAME000, *mDataFile, team),
  mStatSprite(mDataFile->GetData(FRAME000), team), mSound(name) {

  delete mDataFile;

}
