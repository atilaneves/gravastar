#ifndef CPROJBLUEPRINT_H
#define CPROJBLUEPRINT_H


#include "CExplosiveBluePrint.hpp"
#include "CSound.hpp"
#include "CShipStatSprite.hpp"
class CTeam;
class CDataFile;
class CProjYard;


class CProjBluePrint {

  friend class CProjectile;
  friend class CProjSpecial;
  friend class CWeapon;

public:

  CProjBluePrint(const std::string &name, const CTeam &team);

  const CSpriteVector& GetSprites() const {
    return mExplosiveBluePrint.GetSprites(); }


private:

  CDataFile *mDataFile;
  const CTeam& mTeam;
  CExplosiveBluePrint mExplosiveBluePrint;
  float mMaxDamage, mMaxHull, mShockWaveForce, mMass;
  CShipStatSprite mStatSprite;
  CSound mSound;
  CMoverBluePrint mShadowBluePrint;

  void SetAttributes(char *data);

};


#endif
