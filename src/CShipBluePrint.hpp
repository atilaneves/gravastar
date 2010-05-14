#ifndef CSHIPBLUEPRINT_H
#define CSHIPBLUEPRINT_H


#include "CExplosiveBluePrint.hpp"
#include "CProjBluePrint.hpp"
#include "CFollowBluePrint.hpp"
#include "CSound.hpp"
#include "CShipStatSprite.hpp"
#include "CShipSounds.hpp"
#include <memory>
class CTeam;
class CDataFile;
class CShipYard;


class CShipBluePrint {

  friend class CEngine;
  friend class CNose;
  friend class CShipAura;
  friend class CSpecial;
  friend class CProjSpecial;
  friend class CFollowSpecial;
  friend class CShip;
  friend class CWeapon;
  friend class CSuper;
  friend class CPhantom;
  friend class CVoidhar;
  friend class CSoliton;
  friend class CGamma;


public:

  enum { kNbSuperExpSprites = 8, kNbSpecialExpSprites = 10 };

  CShipBluePrint(const std::string &name, const CTeam &team,
		 const CShipYard &shipYard);

  const CGravSprite& GetSprite() const {
    return *(GetSprites())[0];
  }

  const CSpriteVector& GetSprites() const {
    return mExplosiveBluePrint.GetSprites(); }

  const CSpriteVector& GetExaustSprites() const {
    return mExaustBluePrint.GetSprites(); }

  const CShipStatSprite* GetStatSprite() const {
    return &mStatSprite; }


private:

  std::string mName;
  CDataFile *mDataFile;
  const CTeam& mTeam;
  CExplosiveBluePrint   mExplosiveBluePrint;
  CMoverBluePrint       mExaustBluePrint;
  CMoverBluePrint       mInvulnerableBluePrint;
  CMoverBluePrint       mScrambleBluePrint;
  CMoverBluePrint       mEMPBluePrint;
  std::auto_ptr<CProjBluePrint>  mWeaponBluePrint;
  std::auto_ptr<CProjBluePrint>  mExtraProjBluePrint;
  std::auto_ptr<CProjBluePrint>  mProjSpecBluePrint;
  std::auto_ptr<CFollowBluePrint> mFollowSpecBluePrint;
  std::auto_ptr<CFollowBluePrint> mExtraFollowBluePrint;
  float mMass, mMaxHull, mThrust, mMaxVel, mTurnPower;
  int mFastRate, mSlowRate;
  float mMaxTemperature, mCoolingRate;
  int mSpecialRate;
  float mMaxGauge, mDepletion, mRecovery;
  float mBaseHull, mBaseSpecial;
  int mSuperRate;
  float mSuperDuration;
  CShipSounds mSounds;
  CShipStatSprite mStatSprite;
  CGravSprite     mAuraSprite;
  CGravSprite     mSuperSprite;
  CSpriteVector   mSpecialExpSprites;
  CSpriteVector   mSuperExpSprites;

  void SetAttributes(char *data);

};


#endif
