#include "CShipBluePrint.hpp"
#include "CDataFile.hpp"
#include "CShipYard.hpp"
#include "CProjBluePrintFactory.hpp"
#include "CFollowBluePrintFactory.hpp"
#include "CWeaponBluePrintFactory.hpp"
#include "CSpecialExplosion.hpp"
#include "CSuperExplosion.hpp"
#include "deltadat.h"
#include "gravdat.h"



CShipBluePrint::CShipBluePrint(const std::string &name, const CTeam &team,
                               const CShipYard &shipYard):
  mName(name), mDataFile(new CDataFile("Ships/" + name + ".dat")),
  mTeam(team),
  mExplosiveBluePrint(BLUE_000, "ship", *mDataFile, team),
  mExaustBluePrint(EXAUST_000, *mDataFile, team),
  mInvulnerableBluePrint(BLUE_000, *mDataFile, team, team.GetDarkColour()),
  mScrambleBluePrint(1, CDataFile("Weapons/boomerang.dat"),
                     team, team.GetDarkColour()),
  mEMPBluePrint(1, CDataFile("Weapons/emp.dat"),
                team, team.GetDarkColour()),
  mSounds(shipYard.GetSounds()),
  mStatSprite(mDataFile->GetData(BLUE_000), team),
  mAuraSprite(mDataFile->GetData(AURA_000), team),
  mSuperSprite(CDataFile("grav.dat").GetData(GRAV_SUPER_ICON), team) {

  SetAttributes((char*)mDataFile->GetData(ATTRIBUTES_SHIP));
  delete mDataFile;

  CProjBluePrintFactory& projFactory = CProjBluePrintFactory::Instance();
  mProjSpecBluePrint.reset(projFactory.CreateObject(name, team));

  CFollowBluePrintFactory& flwFactory = CFollowBluePrintFactory::Instance();
  mFollowSpecBluePrint.reset(flwFactory.CreateObject(getFollowName(name),
                                                        team));
  mExtraFollowBluePrint.reset(flwFactory.CreateObject(getExtraFollowName(name),
                                                      team));

  CWeaponBluePrintFactory& weapFactory = CWeaponBluePrintFactory::Instance();
  mWeaponBluePrint.reset(weapFactory.CreateObject(getWeaponName(name), team));
  mExtraProjBluePrint.reset(weapFactory.CreateObject(getExtraWeaponName(name),
                                                     team));

  CDataFile specData("Explosions/specialExp.dat");
  for(int i = 0; i < CSpecialExplosion::kNbFrames; ++i)
    mSpecialExpSprites.push_back(new CGravSprite(specData.GetData(i), team));

  CDataFile superData("Explosions/superExp.dat");
  for(int i = 0; i < CSuperExplosion::kNbFrames; ++i)
    mSuperExpSprites.push_back(new CGravSprite(superData.GetData(i), team));
}


void CShipBluePrint::SetAttributes(char *data) {

  std::string fmt="%*s %*s %*s %f %f %f ";
  fmt += "%*s %*s %f %f %*s %*s %*s %*s %d %d %f %f  ";
  fmt += "%*s %*s %*s %*s %d %f %f %f  %*s %*s %f %f ";
  fmt += "%*s %*s %d %f";  //super rate and duration
  
  sscanf(data, fmt.c_str(),
         &mMass, &mMaxHull, &mMaxVel,
         &mThrust, &mTurnPower,
         &mFastRate, &mSlowRate, &mMaxTemperature, &mCoolingRate,
         &mSpecialRate, &mMaxGauge, &mDepletion, &mRecovery,
         &mBaseHull, &mBaseSpecial,
         &mSuperRate, &mSuperDuration);
}
